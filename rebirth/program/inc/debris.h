#pragma once

#include "GameBase.h"
#include "ShapeBase.h"
#include "moveable.h"

class Debris : public GameBase
{
	typedef GameBase Parent;

	DECLARE_PERSISTENT(Debris);

	enum
	{
		netInit = 0x01, netUpdate = 0x02
	};
	enum
	{
		SphereCollisions = 0, BoxCollisions = 1, DetailedCollisions = 2
	};

	class debrisRenderImage : public FearRenderImage
	{
		bool  useLighting;
		float lightCoefficient;

	public:
		//TMat3F transform;
		//TSShapeInstance * shape;
		bool animated;
		int lastDetail;
		//void render(TSRenderContext &rc) override;

		void setLighting(float lc)
		{
			lightCoefficient = lc; useLighting = true;
		}
		void clearLighting()
		{
			useLighting = false;
		}
		bool lightingOn()
		{
			return useLighting;
		}
		float getLighting()
		{
			return lightCoefficient;
		}

		debrisRenderImage()
		{
			shape = 0; animated = false; lastDetail = -1; useLighting = false;
		}
	};

public:
	struct DebrisData : public GameBaseData
	{
		typedef GameBaseData Parent;

		int type;

		float damageThreshold;
		
		int collisionDetail;
		SimTime animRestartTime;
		int animationSequence;

		SimTime minTimeout;
		SimTime maxTimeout;

		float friction;

		int collisionMask;
		int knockMask;

		float damage;
		bool explodeOnRest;
		float elasticity;
		float mass;
		const char* pShapeName;
		int spawnedExplosionID;
		float explodeOnBounce; 
		float spawnedDebrisStrength;

		int imageType;
		int imageSortValue;
		int spawnedDebrisMask;
		float spawnedDebrisRadius;

		float center[3];

		float p;

		DebrisData();
		void pack(BitStream* bs) override;
		void unpack(BitStream* bs) override;
	};

public: //private:
	
	int spawnedExplosionId;
	int gridPoly;
	Point3F avgLV;
	Point3F avgAV;
	bool ghostMe;
	float debrisMass;
	float spawnImpulse;
	SimTime spawnTimeout;	
	SimTime timeout;
	bool explodeOnRest;
	bool hitLastTime;
	float explodeProb;
	float* shapeDetailScale;
	SimTime lastUpdateTime;
	bool inCloud;
	bool hitThisTime;
	
	float elastic; // Bool?	
	int timerCounter;
	float sinkDepth;
	bool underSurfaceLastTime;
	float potentialEnergyDeficit;
	bool underSurfaceThisTime;
	float damage;
	Point3F radii;
	const char* shapeName;
	int animationSequence;

	SimTime reanimateTime;
	SimTime animRestartTime;

	SimTime duration;

	Debris(const Debris& from);
	
	virtual void setShape(int _replaceMass, int _replaceAnimation, float _replaceRestart);
	virtual void setShape(const char* _replaceName, int _replaceMass, int _replaceAnimation, float _replaceRestart);
	virtual void setDuration(float _duration);
	virtual void setCollisionMask(int _newMask);
	virtual void finishAddToManager();
	virtual void initShape();
	
	
	virtual bool bounce(TMat3F& objectToWorld, Point3F& normal, float k);
	virtual bool bounceSphere(Point3F& normal);
	virtual bool bounce(SimMovementInfo* minfo);
	
	virtual void createOnClients(Debris* debris, SimManager* mgr, float scopeDist);

protected:
	DebrisData * m_debrisData;
	debrisRenderImage image;
	SimTime debrisTime;
	bool expire;
	// TODO: Belong here?
	SimCollisionSphereImage collisionImage;

	int getDatGroup() override;
	bool initResources(GameBaseData* io_pDat) override;
	bool processEvent(const SimEvent* event) override;
	bool onAdd() override;
	void onRemove() override;
	bool processCollision(SimMovementInfo* moveInfo) override;
	bool getImageList(const Point3F& pos, ImageList* list) override;
	bool processQuery(SimQuery* query) override;
	void unpackUpdate(Net::GhostManager * gm, BitStream * stream) override;
	DWORD packUpdate(Net::GhostManager* gm, DWORD mask, BitStream* stream) override;
	bool onSimRenderQueryImage(SimRenderQueryImage* query);
	bool onSimCollisionImageQuery(SimCollisionImageQuery* query);
	bool onSimMessageEvent(const SimMessageEvent*);
	
public:
	Debris() :
		spawnedExplosionId(0),
		gridPoly(0),
		ghostMe(false),
		debrisMass(0),
		spawnImpulse(0),
		spawnTimeout(0),
		timeout(0),
		explodeOnRest(false),
		hitLastTime(false),
		explodeProb(0),
		shapeDetailScale(nullptr),
		lastUpdateTime(0),
		inCloud(false),
		hitThisTime(false),
		elastic(0),
		timerCounter(0),
		sinkDepth(0),
		underSurfaceLastTime(false),
		potentialEnergyDeficit(0),
		underSurfaceThisTime(false),
		damage(0),
		shapeName(nullptr),
		animationSequence(0),
		reanimateTime(0),
		animRestartTime(0),
		duration(0),
		m_debrisData(nullptr),
		debrisTime(0),
		expire(false)
	{
	}

	// TODO: Default false?
	Debris(int in_datFileId, float spawnTO, bool ghost = false);
	virtual ~Debris();

	virtual bool onSimTimerEvent(const SimTimerEvent* event);

	virtual int getCollisionMask() const
	{
		return this->collisionMask;
	}
};

class DebrisCloud : public SimContainer
{
	// TODO Guess SimContainer?
	typedef SimContainer Parent;

	friend class PartDebrisCloud;

	DECLARE_PERSISTENT(DebrisCloud);

public:
	static float detailScale;

public: //private:

	class Database sealed : public SimContainerDatabase
	{
	protected:		
		
		bool add(SimContainer* object) override;
		bool remove(SimContainer* object) override;
		bool findIntersections(const SimContainerQuery&, SimContainerList*) override;
		bool findContained(const SimContainerQuery&, SimContainerList*) override;
		SimContainer* findOpenContainer(const SimContainerQuery&) override;
		bool removeAll(SimContainer*) override;
		void render(SimContainerRenderContext& rc) override;
		void scope(SimContainerScopeContext&) override;		

	public:
		VectorPtr<Debris*> debrisList;
		bool inTimer;
		int unionCollisionMask;

		void update(SimContainer* object) override;
		void update(SimContainer* object, SimContainer* cnt);
	};		

	SimContainerList intersectionList;

	float mass;
	Int32 debrisMask;
	Point3F pos;
	float radius;
	Point3F vel;
	float outwardImpulse;
	Point3F axis;
	float angleRange;
	Point3F incomingImpulse;
	float spawnTimeout;
	int soundId;
	DebrisCloud* spawnedFrom;
	bool dataReceived;

	Point3F axes[3];

	DebrisCloud(const DebrisCloud& cloud);
	
	

	void getAxes(const Point3F& axis, Point3F* axes, float& angleRange);
	void toss(Debris* debris, const Point3F& pos, float radius, const Point3F& vel, float outwardImpulse, const Point3F* axes, float angleRange, const Point3F& incomingImpulse, SimManager* mgr);
	void createOnClients(DebrisCloud* cloud, SimManager* mgr, float scopeDist);	
	
	void finishAddToManager();
	bool onSimTimerEvent(const SimTimerEvent* event);
	bool onSimMessageEvent(const SimMessageEvent*);

protected:
	
	bool processEvent(const SimEvent* event) override;
	bool onAdd() override;
	void unpackUpdate(Net::GhostManager*, BitStream* stream) override;
	DWORD packUpdate(Net::GhostManager*, DWORD, BitStream* stream) override;
	bool updateObject(SimContainer* object) override;
	
public:
	DebrisCloud();
	DebrisCloud(float kg, Int32 typeMask, const Point3F& p, float r, const Point3F& v, float outJ, const Point3F& ax, float angleR, const Point3F& inJ, float spawnTO);
	virtual ~DebrisCloud();

	Database database;

	void setSpawnedFrom(DebrisCloud* _sf);

	virtual void addCollisionMask(const int value)
	{
		this->debrisMask |= value;
	}

	virtual SimContainerList& getIntersections()
	{
		return intersectionList;
	}
};

struct DebrisTable
{
	struct ShortListEntry
	{
		int index;
		float mass;
		float p;
	};

	typedef Vector<ShortListEntry> ShortList;

	static float getShortList(float mass, Int32 typeMask, ShortList& sl);
};
