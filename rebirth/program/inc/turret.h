#pragma once

#include "sensor.h"

class Turret : public Sensor
{
	typedef Sensor Parent;

	DECLARE_PERSISTENT(Turret);

public:
	struct TurretData : public SensorData
	{
	private:
		typedef SensorData Parent;

	public:
		float gunRange;
		float speed;
		float minGunEnergy;
		float maxGunEnergy;
		float FOV;
		int fireSound;
		int activationSound;
		int deactivateSound;
		int whirSound;
		float deflection;
		float targetableFovRatio;
		bool isSustained;
		SimTime reloadDelay;
		SimTime firingTime;
		float energyRate;
		float speedModifier;
		ProjectileDataType projectile;

		TurretData();
		void pack(BitStream* stream) override;
		void unpack(BitStream* stream) override;
	};

public: //private:
	TSShapeInstance::Thread* elevationThread;
	TSShapeInstance::Thread* rotationThread;
	TSShapeInstance::Thread* animThread;

	float turretElevation;
	float turretRotation;

	SimTime waitTime;

	float maxElevation;
	float minElevation;

	float maxRotation;
	float minRotation;

	bool hasFocus;
	int fireCount;

	SimTime sleepTime;

	float projectileSpeed;

	Player* primaryTarget;
	int targetsTracked;
	Player* m_pTarget;

	int updateSkip;

	enum
	{
		RETRACTED,
		RETRACTING,
		EXTENDING,
		EXTENDED
	};
	int state;

	// TODO: Values
	enum
	{
		Waiting,
		Firing,
		Reloading
	};
	int m_fireState;

	SimTime m_beganState;

	TurretData* data;
	SFX_HANDLE whirSound;
	SFX_HANDLE fireSound;

	int cameraNode;
	int gunNode;
	int fireSequence;
	int powerSequence;
	Projectile* m_pProjectile;

	PlayerMove lastPlayerMove;

	const Vector3F& getCompassRotation() override;
	virtual void setFireThread();
	virtual bool setPowerThread();
	virtual bool isControlable();

	virtual float elevation(float dx, float dy, float dz);
	virtual float rotation(float dx, float dy);
	virtual bool inDeadZone(float desRot, float desEle);
	virtual void leadPosition(Point3F pos, Point3F vel, float dist, Point3F* leadPos);
	virtual void wrapRotation();
	virtual void wrapElevation();
	virtual void shoot(bool playerControlled, Player* targetPlayer = nullptr);
	virtual void unshoot();
	virtual bool isTargetable(Player* player, float* minDist, float useRange);
	virtual Player* chooseTarget();
	virtual void trackAndFire(Player* closePlayer, float interval);
	virtual void extend(float interval);
	virtual void retract(float interval);
	virtual bool getWeaponAmmoType(ProjectileDataType& out_rPrimary, ProjectileDataType& out_rSecondary);
	virtual void getNodeOffset(TMat3F* trans, char* nodeName, int Node);
	virtual void updateMove(PlayerMove* move, float interval);
	virtual void serverProcessWaiting(DWORD in_currTime);
	virtual void serverProcessReloading(DWORD in_currTime);
	virtual void serverProcessFiring(DWORD in_currTime);

protected:
	enum
	{
		TRotationMask = LastMaskBit,
		ElevationMask = LastMaskBit << 1,
		ShootingMask = LastMaskBit << 2,
		StateMask = LastMaskBit << 3,
		LastMaskBit = LastMaskBit << 4
	};

	bool initResources(GameBaseData* in_data) override;
	bool onAdd() override;
	void onRemove() override;
	void setTeam(int teamId) override;
	bool onSimRenderQueryImage(SimRenderQueryImage* query);
	bool processQuery(SimQuery* query) override;
	bool detectItem(GameBase* object) override;
	void serverProcess(DWORD time) override;
	void clientProcess(DWORD curTime) override;
	bool cameraZoomAndCrosshairsEnabled() override;
	void getCameraTransform(float camDist, TMat3F* transform) override;
	bool getMuzzleTransform(int, TMat3F* transform) override;
	const TMat3F& getEyeTransform() override;
	void serverUpdateMove(PlayerMove* moves, int moveCount) override;
	void buildScopeAndCameraInfo(Net::GhostManager* cr, CameraInfo* camInfo) override;
	void onDamageStateChange(DamageState oldState) override;
	void readPacketData(BitStream* bstream) override;
	void writePacketData(BitStream* bstream) override;
	void inspectRead(Inspect* i) override;
	void inspectWrite(Inspect* i) override;
	DWORD packUpdate(Net::GhostManager* g, DWORD mask, BitStream* stream) override;
	void unpackUpdate(Net::GhostManager* g, BitStream* stream) override;
	Error write(StreamIO& sio, int, int) override;
	Error read(StreamIO& sio, int, int) override;
	int getDatGroup() override;
	void onDeleteNotify(SimObject* io_pDelete) override;
	void onPowerStateChange(GameBase* generator) override;

public:
	Turret();
	~Turret();

	virtual bool setPrimaryTarget(Player* target);
};
