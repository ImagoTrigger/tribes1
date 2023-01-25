#pragma once

#include "GameBase.h"
#include "ShapeBase.h"
#include "fxRenderImage.h"
#include "SimLightGrp.h"

class Explosion sealed : public GameBase
{
	typedef GameBase Parent;

	DECLARE_PERSISTENT(Explosion);

public:
	struct ExplosionData sealed : public GameBaseData
	{
		typedef GameBaseData Parent;

		const char* pShapeName;
		int soundId;
		float timeScale;
		bool faceCamera;
		bool randomSpin;		

		bool hasLight;		
		float lightRange;
		DWORD timeZero;
		DWORD timeOne;
		ColorF colors[3];
		float radFactors[3];

		bool shiftPosition;

		Resource<TSShape> m_expRes;

		ExplosionData();
		void pack(BitStream* bs) override;
		void unpack(BitStream* bs) override;
		bool preload(ResourceManager *rm, bool server, char errorBuffer[256]) override;
	};

public: //private:
	static bool sm_useDynamicLighting;

	fxRenderImage m_renderImage;

	ExplosionData* m_explosionData;
	TSLight m_light;
	Point3F m_axis;
	Point3F m_position;
	DWORD m_timeZeroMS;
	DWORD m_timeOneMS;
	DWORD m_spawnTime;
	DWORD m_expireTime;
	DWORD m_lastUpdated;
	Resource<TSShape> m_hShape;

	Box3F m_bbox;

	TSShapeInstance::Thread* m_pVisThread;

	void loadResources();
	bool onSimRenderQueryImage(SimRenderQueryImage* query);
	bool onSimLightQuery(SimLightQuery* query);
	
	
protected:
	bool initResources(GameBaseData* io_pDat) override;
	int getDatGroup() override;
	bool onAdd() override;
	void onRemove() override;
	bool processQuery(SimQuery* query) override;
	void clientProcess(DWORD in_currTime) override;
	void buildContainerBox(const TMat3F& in_rMat, Box3F* out_pBox) override;

public:
	explicit Explosion(const Int32 in_datFileId);

	Explosion() :
		m_explosionData(nullptr),
		m_timeZeroMS(0),
		m_timeOneMS(0),
		m_spawnTime(0),
		m_expireTime(0),
		m_lastUpdated(0),
		m_pVisThread(nullptr)
	{
	}

	void setPosition(const Point3F& in_rPosition);
	void setAxis(const Point3F& in_rAxis);
	static void applyRadiusDamage(SimManager* manager, int type, const Point3F& pos, const Point3F& vec, float radius, float damageValue, float force, int srcObjectId);
};
