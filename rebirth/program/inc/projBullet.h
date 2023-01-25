#pragma once

#include "Projectile.h"

class Bullet : public Projectile
{
	typedef Projectile Parent;

	DECLARE_PERSISTENT(Bullet);

public:
	struct BulletData : ProjectileData
	{
	private:
		typedef ProjectileData Parent;
		
	public:
		
		BulletData();
		void pack(BitStream* bs);
		void unpack(BitStream* bs);
		bool getTargetVector(const Point3F& in_rShootFrom, const Point3F& in_rShootTo, const float, Point3F* out_pVector, bool* out_pInRange, const bool in_secondTarget);
		float rotationPeriod;
		int bulletHoleIndex;
		float tracerLength;
	} *m_pBulletData;

	struct TracerRenderImage : fxRenderImage
	{
		Point3F m_endPoint;
		Point3F m_startPoint;
		float m_factor;
		void render(TSRenderContext& io_rRC);
	} m_tracerImage;

	Point3F m_interpTo;
	Vector3F m_spawnVelocity;
	float m_spawnVelocityLen;
	Vector3F m_spawnPosition;
	DWORD m_finalTime;
	Point3F m_finalPosition;
	Point3F m_finalNormal;
	SimCollisionInfo storedInfo;
	SimObject* m_finalObject;

	static const Int32 csm_normalBits;

	bool m_resetInterpFrom;
	bool m_isTracer;
	SimCollisionSphereImage m_sphereCollImage;
	DWORD m_spawnTime;
	DWORD m_startInterp;
	DWORD m_endInterp;
	Vector3F m_interpFrom;

	Bullet(const Int32 in_datFileId);
	Bullet();
	bool applyBaseDamage(SimCollisionInfo& io_rCollision, SimObject* io_pHit);
	bool onAdd();
	void buildContainerBox(const TMat3F& in_rMat, Box3F* out_pBox);
	void writeInitialPacket(Net::GhostManager* gm, BitStream* pStream);
	void readInitialPacket(Net::GhostManager* io_pGM, BitStream* pStream);
	DWORD packUpdate(Net::GhostManager* gm, DWORD mask, BitStream* stream);
	void unpackUpdate(Net::GhostManager* gm, BitStream* stream);
	void clientProcess(DWORD in_currTime);
	void predictForward(const DWORD in_currTime, const DWORD in_predictTime, Point3F& out_rPosition);
	Int32 getBulletHoleIndex(SimCollisionInfo& io_rCollision);
	int getDatGroup();

	using Projectile::spawnImpactEffect;
	void spawnImpactEffect(SimCollisionInfo& io_rCollision);
	
	void readExplosion(BitStream* io_pStream);
	void writeExplosion(BitStream* io_pStream);
	SimCollisionImage* getSelfImage();
	bool initResources(GameBase::GameBaseData* io_pDat);
	bool processQuery(SimQuery* query);
	bool onSimRenderQueryImage(SimRenderQueryImage* query);
	bool onSimLightQuery(SimLightQuery* query);
	void setSearchBoundaries();
	void serverProcess(DWORD in_currTime);
};
