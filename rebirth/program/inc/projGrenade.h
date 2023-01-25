#pragma once

#include "Projectile.h"
#include "sfx.strings.h"


class Grenade : public Projectile
{
	typedef Projectile Parent;

	DECLARE_PERSISTENT(Grenade);

public:
	enum
	{
		FGCollisionSoundMask = LastMaskBit,
		LastMaskBit = LastMaskBit << 1
	};

	struct GrenadeData : ProjectileData
	{
	private:
		typedef ProjectileData Parent;

	public:

		float elasticity;
		const char* pSmokeName;

		Resource<TSShape> smokeShape;

		GrenadeData();
		void pack(BitStream* bs);
		void unpack(BitStream* bs);
		bool preload(ResourceManager * rm, bool server, char errorBuffer[256]);
		bool getTargetVector(const Point3F& in_rShootFrom, const Point3F& in_rShootTo, const float in_gravity, Point3F* out_pVector, bool* out_pInRange, const bool in_secondTarget);
	} *m_pGrenadeData;

	int m_lastSurfaceType;
	bool m_primedExplosion;
	DWORD m_primerTime;
	double m_lastPuff;
	UInt32 m_puffInterval;
	DWORD m_lastGhosted;

	bool initResources(GameBase::GameBaseData* io_pDat);
	Grenade(const Int32 in_datFileId);
	Grenade();
	bool onAdd();
	void buildContainerBox(const TMat3F& in_rMat, Box3F* out_pBox);
	void writeInitialPacket(Net::GhostManager* gm, BitStream* pStream);
	void readInitialPacket(Net::GhostManager* gm, BitStream* pStream);
	DWORD packUpdate(Net::GhostManager* gm, DWORD mask, BitStream* stream);
	void unpackUpdate(Net::GhostManager* gm, BitStream* stream);
	void clientProcess(DWORD in_currTime);
	void serverProcess(DWORD in_currTime);
	void destroyProjectile();
	void updateTrail(DWORD in_currTime);
	void playBounceSound(const int in_surfaceType);
	int getDatGroup();
	void readExplosion(BitStream*);
	void writeExplosion(BitStream*);
	bool losStep(TMat3F& io_rPosition, DWORD& io_rTime);
	bool processSurface(Vector3F normal, const CollisionSurface& surface, BitSet32);
};
