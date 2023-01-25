#pragma once

#include "Projectile.h"

class SimpleSwooshTrail;

class RocketDumb : public Projectile
{
	typedef Projectile Parent;

	DECLARE_PERSISTENT(RocketDumb);

public:

	struct RocketDumbData : ProjectileData
	{
	private:
		typedef ProjectileData Parent;

	public:

		enum
		{
			None,
			Swoosh,
			Smoke
		};
		int trailType;
		const char* trailString;
		float trailLength;
		float trailWidth;
		Resource<GFXBitmap> trailBitmap;
		Resource<TSShape> smokeShape;

		RocketDumbData();
		void pack(BitStream* bs);
		void unpack(BitStream* bs);
		bool preload(ResourceManager * rm, bool server, char errorBuffer[256]);
		float getTerminalVelocity() const;
		bool getTargetVector(const Point3F& in_rShootFrom, const Point3F& in_rShootTo, const float, Point3F* out_pVector, bool* out_pInRange, const bool in_secondTarget);
	}*m_pRocketData;

	bool m_timeoutExplosion;
	Point3F m_lastPuffPos;
	Vector3F m_accelVector;
	Point3F m_interpFrom;
	Point3F m_interpTo;
	DWORD m_endInterp;
	int m_startInterp;
	DWORD m_lastGhosted;
	SimpleSwooshTrail* m_pSwooshImage;

	RocketDumb(const Int32 in_datFileId);
	RocketDumb();
	int getDatGroup();
	virtual ~RocketDumb();
	bool initResources(GameBase::GameBaseData* io_pDat);
	bool onAdd();
	void buildContainerBox(const TMat3F& in_rMat, Box3F* out_pBox);
	void writeInitialPacket(Net::GhostManager* gm, BitStream* pStream);
	void readInitialPacket(Net::GhostManager* gm, BitStream* pStream);
	DWORD packUpdate(Net::GhostManager* gm, DWORD mask, BitStream* stream);
	void unpackUpdate(Net::GhostManager* gm, BitStream* stream);
	void setTerminalVelocity();
	void predictForward(const DWORD in_currTime, const DWORD in_predictTime, Point3F& out_rPosition);
	void clientProcess(DWORD in_currTime);
	void serverProcess(DWORD in_currTime);
	void destroyProjectile();
	bool processQuery(SimQuery* query);
	bool onSimRenderQueryImage(SimRenderQueryImage* query);
	void updateTrail();
	void readExplosion(BitStream* io_pStream);
	void writeExplosion(BitStream* io_pStream);
};
