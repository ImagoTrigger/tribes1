#pragma once

#include "ShapeBase.h"
#include "FearPlayerPSC.h"
#include "ProjectileFactory.h"
#include "netGhostManager.h"

class Vehicle : public StaticBase
{
	typedef StaticBase Parent;

	DECLARE_PERSISTENT(Vehicle);

public:
	struct VehicleData : public StaticBaseData
	{
	private:
		typedef StaticBaseData Parent;

	public:

		float minSpeed;
		float maxSpeed;
		SimTime reloadDelay;
		ProjectileDataType projectile;

		int ramDamageType;
		float ramDamage;
		bool visibleDriver;

		float mass;
		float drag;
		float density;

		int idleSound;
		int moveSound;
		int damageSound;
		int fireSound;
		int mountSound;
		int dismountSound;
		int driverPose;


		Point3F suspension[4];

		VehicleData();
		void pack(BitStream* stream) override;
		void unpack(BitStream* stream) override;
	};

public: //private:

	static float prefVehicleShadowSize;


	VehicleData* data;





	Point3F lastPos;
	Point3F lastRot;
	Point3F savedPos;
	Point3F savedRot;

	int updateSkip;




	int fireCount;

	SimTime waitTime;

	int updateDebt;

	int interpDoneTime;
	int eyeNode;
	int gunCount;
	int gunNode;
	int* muzzleNodes;

	int passengerCount;
	int maxPassengers;
	int* passengerNodes;

	int exitNode;
	int pilotNode;

	SFX_HANDLE idleSound;
	SFX_HANDLE throttleSound;




	float lastPitch;






	virtual void clearMount();
	virtual bool mountRender();


	virtual void switchSoundState(int newState);
	virtual bool onSimTimerEvent(const SimTimerEvent*);
	virtual bool onSimCollisionImageQuery(SimCollisionImageQuery* query);
	virtual void initGuns();
	virtual void initPassengers();

	virtual void ghostSetMove(PlayerMove* move, Point3F* newPos, Point3F* newRot, float newSpeed, float newLift, int skipCount);



protected:
	int CollisionDamageMask;//= SimTerrainObjectType | SimInteriorObjectType;



	//ShapeCollisionImage collisionImage;

	// TODO: Enum values
	enum
	{
		SoundMask = LastMaskBit,
		StatusMask = LastMaskBit << 2,
		ShootingMask = LastMaskBit << 3,
		LastMaskBit = LastMaskBit << 4
	};

	// TODO: Enum values
	enum
	{
		NO_SOUND,
		IDLE_SOUND,
		RUN_SOUND
	};
	int soundState;

	Point3F velocityVector;
	float fallVelocity;
	float trackVelocity;
	bool hasFocus;
	float speed;
	float lift;
	Point3F desiredRot;
	float desiredSpeed;
	bool onGround;
	PlayerMove lastPlayerMove;

	virtual void shoot();
	virtual bool updateMove(PlayerMove*, float interval);

	bool onAdd() override;
	void onRemove() override;
	bool initResources(GameBaseData* in_data) override;
	void clientProcess(DWORD curTime) override;
	void serverProcess(DWORD) override;
	void onCollisionNotify(GameBase* object) override;
	bool onSimObjectTransformEvent(const SimObjectTransformEvent* event);
	void setDamageLevel(float level) override;
	bool processEvent(const SimEvent* event) override;
	bool onSimRenderQueryImage(SimRenderQueryImage* query);
	void scriptOnCollision(GameBase* obj) override;
	bool processQuery(SimQuery* query) override;
	void setPlayerControl(bool ctrl) override;
	bool cameraZoomAndCrosshairsEnabled() override;
	bool getMuzzleTransform(int slot, TMat3F* transform) override;
	void getCameraTransform(float camDist, TMat3F* transform) override;
	const TMat3F& getEyeTransform() override;
	void serverUpdateMove(PlayerMove* moves, int moveCount) override;
	bool processBlocker(SimObject* obj) override;
	void readPacketData(BitStream* bstream) override;
	void writePacketData(BitStream* bstream) override;
	int getDatGroup() override;
	DWORD packUpdate(Net::GhostManager* g, DWORD mask, BitStream* stream) override;
	void unpackUpdate(Net::GhostManager* gm, BitStream* stream) override;
	Error read(StreamIO& sio, int, int) override;
	Error write(StreamIO& sio, int, int) override;



public:
	static float prefShapeDetail;

	Vehicle();

	void getObjectMountTransform(int mountPoint, TMat3F* transform) override;

	virtual bool canRide(GameBase*);
	virtual bool canMount(GameBase*);

	virtual void changePassengerCount(int change);

	virtual int nextPassengerPoint() const
	{
		return this->passengerNodes[this->passengerCount];
	}
};
