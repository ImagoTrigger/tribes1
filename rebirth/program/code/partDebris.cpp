#include <PartDebris.h>
#include <ml.h>
#include "explosion.h"
#include <Soundfx.h>
#include "simResource.h"
#include "fearDcl.h"

#define IN_SERVER (manager->isServer())

// a random number generator just for debris stuff
extern Random dbRand;

//------------------------------------------------------------------------------ 

PartDebris::PartDebris(TSPartInstance * _part, int _id, float _spawnTO) :
   Debris(_id,_spawnTO,false)
{
    // set arbitrary mass
    debrisMass = 250;
    setMass(debrisMass);
   image.shape = _part;
}

PartDebris::PartDebris(TSPartInstance * _part, DebrisPartInfo * _chooser, float _spawnTO) :
   Debris(_chooser->id,_spawnTO,false)
{
    // remember chooser for our own later use
    chooser = _chooser;

    // get part radius squared
    Box3F bbox;
    _part->boundsObject->getBox(_part,bbox);
    Point3F span = bbox.fMax-bbox.fMin;
    float radiusSq = m_dot(span,span) * 0.25f;

    // choose proper id
    while (radiusSq > _chooser->radius*chooser->radius || dbRand.getFloat(0.99f)>_chooser->p)
        _chooser++;

    datFileId  = _chooser->id;
    debrisMass = _chooser->mass;
    shapeDetailScale = _chooser->shapeDetailScale;
    setMass(debrisMass);
    image.shape = _part;

    // some proportion of the debris shouldn't be generated due to detailing
    if (dbRand.getFloat(0.99f) > DebrisCloud::detailScale * (1.0f-_chooser->detailScaleMin)
                                 + _chooser->detailScaleMin)
    {
      expire = true;
      spawnTimeout = -spawnTimeout; // don't spawn anything
    }  
}

void PartDebris::initShape()
{
    // image.shape already set
    image.animated = false;
    image.itype = SimRenderImage::Normal;

    // get box around "bounds" object
    // use for bouncing box and detailed collision
    // only use a "tight fit" if radius is small
    Box3F bounceBox;
    TS::ObjectInstance * obj = image.shape->getNode(0)->fObjectList[0];
    obj->getBox(image.shape,bounceBox);

    // set-up collision image
    float rad = 0.5f * (bounceBox.fMax-bounceBox.fMin).lenf();
    collisionImage.radius  = rad;
    collisionImage.center  = (bounceBox.fMin+bounceBox.fMax)*0.5f;

    // set box -- use shapes radius
    boundingBox.fMax = boundingBox.fMin = collisionImage.center;
    boundingBox.fMin.x -= rad; boundingBox.fMin.y -= rad; boundingBox.fMin.z -= rad;
    boundingBox.fMax.x += rad; boundingBox.fMax.y += rad; boundingBox.fMax.z += rad;

    // get box around "bounds" object
    // use for bouncing box and detailed collision
    // only use a "tight fit" if radius is small
    radii  = bounceBox.fMax;
    radii -= bounceBox.fMin;
    radii *= 0.5f;
    if (radii.x < 0.5f)
        radii.x = 0.5f;
    if (radii.y < 0.5f)
        radii.y = 0.5f;
    if (radii.z < 0.5f)
       radii.z = 0.5f;

    // set world space bounding box -- SimMovement methods
    // handle it from now on
    Box3F box;
    buildContainerBox(getTransform(),&box);
    setBoundingBox(box);
}

bool PartDebris::onSimMessageEvent(const SimMessageEvent *event)
{
    if (static_cast<TSPartInstance*>(image.shape)->objectCount==1)
        return Debris::onSimMessageEvent(event);

    float elapsed = (float) manager->getCurrentTime() - debrisTime;
    spawnTimeout -= elapsed;

    // create new debris cloud and explosion?
    if (spawnTimeout>0.0f)
    {
        image.shape->setDetailLevel(0);
        PartDebrisCloud * newCloud = new PartDebrisCloud(image.shape,getTransform(),
                                                         getTransform().p,
                                                         chooser,
                                                         getLinearVelocity(),
                                                         m_debrisData->spawnedDebrisStrength,
                                                         Point3F(0,0,0),
                                                         spawnTimeout);
        newCloud->setBreakProbability(0.65f); // should probably be a parameter to debris cloud...

        if (inCloud)
        {
            DebrisCloud * motherCloud = static_cast<DebrisCloud*>(this->getContainer());
            newCloud->setSpawnedFrom(motherCloud);
        }
        manager->addObject(newCloud);

        if (spawnedExplosionId)
        {
            Explosion * exp = new Explosion(spawnedExplosionId);
            exp->setPosition(getTransform().p);
//            exp->setSound(false);
            manager->addObject(exp);
        }
    }
    manager->deleteObject(this);

    return true;
}

PartDebrisCloud::PartDebrisCloud(PartDebris ** _list, int _listSize)
{
    list = _list;
    listSize = _listSize;

    if (*list)
        transform.p = (*list)->getTransform().p; // used to set initial container position
    else
        transform.p.set(0,0,0);
}

PartDebrisCloud::PartDebrisCloud(TSShapeInstance * shape, const TMat3F & _transform,
                                       const Point3F &p, int _id, 
                                       const Point3F &v, float outJ,
                                       const Point3F & inJ, float spawnTO)
{
    transform = _transform;
    pos = p; // position to "blow out" from
    vel = v;
    outwardImpulse = outJ;
    incomingImpulse = inJ;
    spawnTimeout = spawnTO;
    useBreakP = false;

    cannabalize = shape;

    debrisId = _id;
    chooser = NULL;

    list = NULL;
}

PartDebrisCloud::PartDebrisCloud(TSShapeInstance * shape, const TMat3F & _transform,
                                 const Point3F &p, DebrisPartInfo * _chooser, 
                                 const Point3F &v, float outJ,
                                 const Point3F & inJ, float spawnTO)
{
    transform = _transform;
    pos = p; // position to "blow out" from
    vel = v;
    outwardImpulse = outJ;
    incomingImpulse = inJ;
    spawnTimeout = spawnTO;
    useBreakP = false;

    cannabalize = shape;

    debrisId = -1;
    chooser = _chooser;

    list = NULL;
}

void PartDebrisCloud::setBreakProbability(float p)
{
   useBreakP = true;
   breakP = p;
}

bool PartDebrisCloud::onAdd()
{
    if (!Parent::onAdd())
        return false;
    netFlags.clear(Ghostable);

    // if we are not a spawned debris cloud, add to root container
    if (!spawnedFrom)
    {
        // add ourself to the root and set our bounding box
        SimContainer *root = findObject(manager, SimRootContainerId,root);
        containerMask = 0; // so nothing gets in...
        root->addObject(this);
        setBoundingBox(Box3F(transform.p,transform.p));

        // add to timer Set -- if we're a spawned cloud, we won't do this
        addToSet(SimTimerSetId);
    }

    if (list)
    {
        // generate from a list
        addDebris(list,listSize);
        delete [] list;
    }
    else
        generateDebris();

   if (soundId>0)
      // make sound
      Sfx::Manager::PlayAt( manager, soundId, transform, Point3F(0, 0, 0));

   // nothing got added, delete ourself
   if (database.debrisList.empty())
      SimMessageEvent::post(this,-1);

   return true;
}

void PartDebrisCloud::addDebris(PartDebris ** list, int count)
{
    for (int i=0;i<count;list++,i++)
    {
      // add debris to debris cloud we're spawned from or else add to ourself
      if (spawnedFrom)
      {
         spawnedFrom->database.update(*list, spawnedFrom);
         spawnedFrom->containerMask = -1;
         spawnedFrom->addObject(*list);
         spawnedFrom->containerMask = 0;
      }
      else
      {
         database.update(*list, this);
         containerMask = -1; 
         addObject(*list);
         containerMask = 0; 
      }

        // add to manager
        manager->addObject(*list);
    }
}

void PartDebrisCloud::generateDebris()
{
    Vector<TSPartInstance*> partList;

    TSShapeInstance::NodeInstance * detailNode = cannabalize->getDetail();
    if (!detailNode)
        return; // fDetailLevel probably -1

    if (useBreakP)
       TSPartInstance::breakShape(cannabalize,detailNode,breakP,partList,*SimResource::get(manager));
    else
       TSPartInstance::breakShape(cannabalize,detailNode,partList,*SimResource::get(manager));

    for (int i=0;i<partList.size();i++)
    {
        TSPartInstance * part = partList[i];

        TMat3F partTransform;
        m_mul(part->fRootDeltaTransform,transform,&partTransform);
        part->fRootDeltaTransform.identity();
        Point3F center = partTransform.p;

        PartDebris *debris;
        if (chooser)
          debris = new PartDebris(part,chooser,spawnTimeout);
        else
          debris = new PartDebris(part,debrisId,spawnTimeout);

        debris->setPosition(partTransform,true);

        // set in motion
        debris->setLinearVelocity(vel);

        // outward thrust
        Point3F velvec = center - pos;
        velvec.normalizef();
        velvec *= outwardImpulse;
        debris->applyImpulse(velvec);
        debris->applyImpulse(incomingImpulse);

        // add some random angular velocity
        // magic numbers and all
        float amag = outwardImpulse * 0.005f;
        if (amag>5.0f)
            amag = 5.0f;
        Point3F avel = Point3F(dbRand.getFloat(amag)-amag*0.5f,
                               dbRand.getFloat(amag)-amag*0.5f,
                               dbRand.getFloat(amag)-amag*0.5f);
        debris->setAngulerVelocity(avel);

        addDebris(&debris,1);
   }
    
}
