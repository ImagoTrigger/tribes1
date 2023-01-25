#pragma once
#include "Projectile.h"

class SeekingMissile : public Projectile
{
	typedef Projectile Parent;

	DECLARE_PERSISTENT(SeekingMissile);

public:

	static const DWORD csm_seekUpdateTimeMS;

	struct SeekingMissileData : ProjectileData
	{
	private:
		typedef ProjectileData Parent;

	public:

		float seekingTurningRadius;
		float nonSeekingTurningRadius;
		float proximityDist;

		Resource<TSShape> smokeShape;

		SeekingMissileData();
		void pack(BitStream* bs);
		void unpack(BitStream* bs);
		bool preload(ResourceManager * rm, bool server, char errorBuffer[256]);
	} *m_pMissileData;



	Vector3F m_lastPuffPos;
	bool m_timeoutExplosion;
	bool m_lockLost;
	DWORD m_lastSeekUpdate;
	ShapeBase* m_pTarget;
	bool m_canSeeTarget;
	Point3F m_targetPosition;
	float m_currSeekPercentage;
	float m_angularVel;

	SeekingMissile(const Int32 in_datFileId);
	SeekingMissile();
	virtual ~SeekingMissile();
	int getDatGroup();
	bool initResources(GameBase::GameBaseData* io_pDat);
	bool onAdd();
	void readExplosion(BitStream* io_pStream);
	void writeExplosion(BitStream* io_pStream);
	void adjustVelocity(DWORD in_numMS, Point3F* out_pNewVel);
	void clientProcess(DWORD in_currTime);
	void serverProcess(DWORD in_currTime);
	void killProjectile();
	void destroyProjectile();
	void readInitialPacket(Net::GhostManager* gm, BitStream* pStream);
	void writeInitialPacket(Net::GhostManager* gm, BitStream* pStream);
	DWORD packUpdate(Net::GhostManager* gm, DWORD mask, BitStream* stream);
	void unpackUpdate(Net::GhostManager* gm, BitStream* stream);
	Point3F getTargetDirection();
	Point3F getTargetPosition();
	Point3F getTargetVelocity();
	void buildContainerBox(const TMat3F& in_rMat, Box3F* out_pBox);
	bool isTargetable() const;
	void setTarget(ShapeBase* io_pTarget);
	void onDeleteNotify(SimObject* io_pObject);
	float getTargetRange() const;
	void updateSeekPercentage();
	int getTargetScriptId();
	void updateTrail();
};
