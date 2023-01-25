#pragma once

#include "Debris.h"
#include "ts_partInstance.h"

struct DebrisPartInfo
{
	// debris id
	int id;

	// est. mass for this type
	float mass;

	// max radius for this type
	float radius;

	// probability of selection
	float p;

	float shapeDetailScale; // TODO: This belong here? (Order)

	float detailScaleMin;  // TODO: This belong here? (Order)
};

class PartDebris : public Debris
{	
	DebrisPartInfo* chooser;
	float debrisMass;
	float shapeDetailScale;
	Point3F radii;
	SimTime spawnTimeout;
	int spawnedExplosionId;
	bool inCloud;
	

protected:

	void initShape() override;
	bool onSimMessageEvent(const SimMessageEvent* event);

public:
	PartDebris(TSPartInstance* _part, DebrisPartInfo* _chooser, float _spawnTO);
	PartDebris(TSPartInstance* _part, int _id, float _spawnTO);
};

class PartDebrisCloud : public DebrisCloud
{
	typedef DebrisCloud Parent;

	TMat3F transform;
	Point3F pos;
	Point3F vel;
	float outwardImpulse;
	Point3F incomingImpulse;
	float spawnTimeout;
	bool useBreakP;
	float breakP;
	TSShapeInstance* cannabalize;
	int debrisId;
	DebrisPartInfo* chooser;
	PartDebris** list;
	int listSize;

	DWORD soundId;

	
	
	DebrisCloud* spawnedFrom;

	PartDebrisCloud(PartDebris** _list, int _listSize);	
	
	virtual void addDebris(PartDebris** list, int count);
	virtual void generateDebris();

protected:
	bool onAdd() override;
	
public:
	PartDebrisCloud(TSShapeInstance* shape, const TMat3F& _transform, const Point3F& p, int _id, const Point3F& v, float outJ, const Point3F& inJ, float spawnTO);
	PartDebrisCloud(TSShapeInstance * shape, const TMat3F& _transform, const Point3F& p, DebrisPartInfo* _chooser, const Point3F& v, float outJ, const Point3F& inJ, float spawnTO);
	virtual void setBreakProbability(float p);
};
