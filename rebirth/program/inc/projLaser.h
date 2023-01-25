#pragma once

#include "Projectile.h"

#define NULL nullptr

class LaserProjectile : public Projectile
{
	// TODO: Guess Projectile
	typedef Projectile Parent;

	DECLARE_PERSISTENT(LaserProjectile);

public:

	struct LaserData : public ProjectileData
	{
		typedef ProjectileData Parent;

		const char* pBitmapName;
		const char* pHitShapeName;
		bool detachFromShooter;
		LaserData();
		void pack(BitStream* bs) override;
		void unpack(BitStream* bs) override;
		float getTerminalVelocity() const override;
	};

public: //private:

	fxRenderImage m_hitImage;
	DWORD m_spawnTime;
	TSLight m_endLight;
	DWORD m_endLastReadjusted;
	bool m_hitTarget;
	
	float m_finalDamage;
	

protected:
	Vector3F m_directionVector;
	float m_startIntensity;

	

	struct BeamRenderImage : public SimRenderImage
	{
		Point3F m_startPoint;
		Point3F m_endPoint;
		Point3F m_perpVec;
		float m_endFactor;
		float m_startFactor;
		SimTime m_time;
		Resource<GFXBitmap> m_pBitmap;

		void render(TS::RenderContext& io_rc) override;
	} m_beamRenderImage;


	LaserData* m_laserData;
	Resource<GFXBitmap> m_resLaserBitmap;
	Resource<TSShape> m_resHitShape;
	Point3F m_startPoint;
	Point3F m_endPoint;

	virtual bool readjustEnd();

	void loadResources(const bool in_isGhost) override;
	bool initResources(GameBaseData* io_pDat) override;
	void buildContainerBox(const TMat3F&, Box3F* out_pBox) override;
	bool onAdd() override;
	bool onSimLightQuery(SimLightQuery* query) override;
	bool onSimRenderQueryImage(SimRenderQueryImage* query);
	bool processQuery(SimQuery* query) override;
	void initProjectile(const TMat3F& in_rTrans, const Point3F&, const SimObjectId in_shooterId) override;
	void setEnergy(const float in_energy, const float in_pOfM) override;
	void clientProcess(DWORD in_currTime) override;
	void serverProcess(DWORD in_currTime) override;
	void writeInitialPacket(Net::GhostManager* io_pGM, BitStream* pStream) override;
	void readInitialPacket(Net::GhostManager* io_pGM, BitStream* pStream) override;
	DWORD packUpdate(Net::GhostManager* gm, DWORD mask, BitStream* stream) override;
	void unpackUpdate(Net::GhostManager* gm, BitStream* stream) override;
	int getDatGroup() override;
	void readExplosion(BitStream*) override;
	void writeExplosion(BitStream*) override;

public:
	LaserProjectile();
	explicit LaserProjectile(const Int32 in_datFileId);
	virtual ~LaserProjectile();	
};
