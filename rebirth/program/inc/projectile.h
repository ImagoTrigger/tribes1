#pragma once

#include "Player.h"
#include "SimLightGrp.h"
#include "ShapeBase.h"
#include "fxRenderImage.h"


class Projectile : public GameBase
{
	// TODO: Guess GameBase
	typedef GameBase Parent;



public:
	static const Int32 csm_collisionMask;

	struct ProjectileData : public GameBaseData
	{
	private:
		typedef GameBaseData Parent;

	public:

		const char* bulletShapeName;
		int explosionTag;
		int expRandCycle;
		bool collideWithOwner;
		DWORD ownerGraceMS;
		float collisionRadius;
		float mass;
		int damageClass;
		float damageValue;
		int damageType;
		float explosionRadius;
		float kickBackStrength;
		float aimDeflection;
		float muzzleVelocity;
		float terminalVelocity;
		float acceleration;
		float totalTime;
		float liveTime;
		float projSpecialTime;
		bool projSpecialBool;
		float lightRange;
		ColorF lightColor;
		float inheritedVelocityScale;
		int soundId;

		Resource<TSShape> m_projRes;

		ProjectileData();
		void pack(BitStream* bs) override;
		void unpack(BitStream* bs) override;
		bool preload(ResourceManager * rm, bool server, char errorBuffer[256]) override;
		virtual float getTerminalVelocity() const;
		virtual bool getTargetVector(const Point3F& in_rShootFrom, const Point3F& in_rShootTo, const float, Point3F* out_pVector, bool* out_pInRange, const bool in_secondTarget);
	};

protected:
	static const int csm_damageMask;

	bool m_overrideRender;

	explicit Projectile(const Int32 in_datFileId);

	int getDatGroup() override;
	bool initResources(GameBaseData* io_pDat) override;
	bool onAdd() override;
	void onRemove() override;
	DWORD packUpdate(Net::GhostManager* gm, DWORD mask, BitStream* stream) override;
	void unpackUpdate(Net::GhostManager* gm, BitStream* stream) override;
	void onDeleteNotify(SimObject* io_pDelete) override;
	bool processCollision(MovementInfo* info) override;
	void clientProcess(DWORD in_currTime) override;
	void serverProcess(DWORD in_currTime) override;
	bool processQuery(SimQuery* query) override;

	void buildContainerBox(const TMat3F& in_rMat, Box3F* out_pBox) override;

	virtual void readExplosion(BitStream*) = 0;
	virtual void writeExplosion(BitStream*) = 0;

	virtual void readInitialPacket(Net::GhostManager* io_pGM, BitStream* io_pStream);
	virtual void writeInitialPacket(Net::GhostManager* io_pGM, BitStream* io_pStream);
	ShapeBase* m_pShooter;
	ProjectileData* m_projectileData;
	virtual void loadResources(const bool in_isGhost);

	virtual Int32 getDamageId();
	SimObjectId m_shooterId;
	int m_lastUpdated;
	bool m_faceForward;
	bool m_testCollision;
	SimCollisionSphereImage m_collisionImage;
	fxRenderImage m_renderImage;

	enum
	{
		FPExplosionMask = LastMaskBit,
		FPPositionMask = LastMaskBit << 1,
		FPVelocityMask = LastMaskBit << 2,
		LastMaskBit = LastMaskBit << 3
	};

	bool m_hasExploded;

	DWORD m_ownerGraceMS;

	virtual void stopProjectileSound();
	virtual void applyRadiusDamage(const Point3F& io_rDetonationPoint);
	bool m_waitingForDelete;
	DWORD m_deleteTime;

	virtual void decayGraceTime(const UInt32 in_decayStep);
	DWORD m_totalTime;
	virtual void updateProjectileSound(const TMat3F& in_rTrans, const Point3F& in_rVel);
	virtual Int32 getExplosionTag();
	TSLight m_light;

	DWORD m_liveTime;
	virtual bool moveProjectile(const UInt32 in_currTime, SimCollisionInfo& out_rCollision, SimObject*& out_pObject, const bool in_doCollisions, const bool in_overrideTimeSlice);

	virtual void spawnImpactEffect(const Point3F& in_rPosition);
	virtual void spawnImpactEffect(SimCollisionInfo& io_rCollision);

	Point3F m_explosionPosition;
	Point3F m_explosionAxis;
	int m_explosionId;
	virtual Int32 getExplosionTag(SimCollisionInfo&);
	bool m_renderFacingCamera;
	bool m_projectileIsLive;

	Point3F m_instTerminalVelocity;
	virtual bool isProjStatic(SimObject* pObj);
	virtual Int32 getBulletHoleIndex(SimCollisionInfo&);
	virtual void killProjectile();
	virtual void destroyProjectile();
public: //private:








	SFX_HANDLE m_projectileSound;

	Resource<TSShape> m_bulletRes;
	Point3F m_shooterVel;




	int m_shooterClientLoginId;


	int m_shooterClientId;



	bool onSimRenderQueryImage(SimRenderQueryImage* query);



	virtual bool applyBaseDamage(SimCollisionInfo& io_rCollision, SimObject* io_pHit);



	virtual void deflectProjectile(const float in_deflection);

	virtual bool onSimLightQuery(SimLightQuery * query);

	virtual bool onSimCollisionImageQuery(SimCollisionImageQuery* query);







	virtual float getInheritedVelScale() const;












public:
	virtual ~Projectile();

	virtual void initProjectile(const TMat3F& in_rTrans, const Point3F& in_rShooterVel, const SimObjectId in_shooterId);
	virtual bool isSustained() const;
	virtual bool isTargetable() const;
	virtual float getTargetRange() const;

	virtual void setTarget(ShapeBase*);
	virtual void setEnergy(const float, const float);

	virtual void shutOffProjectile();

	virtual void updateImageTransform(const TMat3F&);
};
