#pragma once

#include "SimContainer.h"
#include "FearDcl.h"
//#include "itrres.h"
#include "GameBase.h"
#include "ts_shape.h"

class SmokeManager : public GameBase
{
	typedef GameBase Parent;

	struct SmokePuff;

public:
	static UInt32 sm_numPuffsAllowed;
	SmokePuff* m_pPuffArray;
	int m_currentlyAllocatedPuffs;
	int m_currentPuff;
	int m_numActivePuffs;
	DWORD m_lastUpdated;


	void clientProcess(DWORD in_currTime);
	void reallocatePuffs();
	bool onAdd() override;
	void onRemove() override
	{
		// TODO: Figure out why this is needed.
		SimMovement::onRemove();
	}
	bool onSimRenderQueryImage(SimRenderQueryImage* query);
	bool processQuery(SimQuery* query);
	void addPuff(const char* in_pPuffName, const float in_puffTime, const Point3F& in_rPuffPosition, const Point3F& in_rPuffVelocity);
	void addPuff(Resource<TS::Shape>& rSmokeShape, const float in_puffTime, const Point3F& in_rPuffPosition, const Point3F& in_rPuffVelocity);
	void removeAllInRadius(Point3F position, float in_radius);

	SmokeManager();
	virtual ~SmokeManager();

	static SmokeManager* get(SimManager* const manager)
	{
		return dynamic_cast<SmokeManager*>(manager->findObject(SmokeManagerId));
	}
};
