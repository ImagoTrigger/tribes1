#pragma once

#include "StaticBase.h"
#include "SimPathManager.h"

// TODO: See if this is used anywhere, suspected dead code.
class MoveableBase : public StaticBase
{
	// TODO: Guess StaticBase, StaticShape instead?
	typedef StaticBase Parent;

public:
	struct MoveableBaseData : public StaticBaseData
	{
	private:
		typedef StaticBaseData Parent;

	public:
		SimTag iStartSoundTag = 0;
		SimTag iStopSoundTag = 0;
		SimTag iRunSoundTag = 0;
		float rForwardDelay = 0.0f;
		float rBackwardDelay = 0.0f;
		int iLinearVelocity = 0;
		float rCrushDamage = 0.0f;
		bool fInvincible = false;

	protected:
		void pack(BitStream* stream) override;
		void unpack(BitStream* stream) override;

	public: //private:
		MoveableBaseData();
	};

public: //private:

	bool fEditing;

	// TODO Order, values
	enum
	{
		NETMASK_INIT = BIT(19),
		NETMASK_SOUND = BIT(20),
		NETMASK_UPDATE = BIT(21),
		NETMASK_WAYPOINT = BIT(22),
		NETMASK_EDIT = BIT(23),
	};

	// TODO: Order
	enum STATE
	{
		STATE_STOP,
		STATE_FORWARD,
		STATE_BACKWARD,
		STATE_WAYPOINT
	};

	Int8 state;

	enum MOVEMENT
	{
		STOP,
		FORWARD,
		BACKWARD,
		WAYPOINT
	};

	SimPathManager* spm;

	int iPathID;
	bool fPathUpdated;
	int iWaypoint;
	int iLastWaypoint;
	int iTargetWaypoint;
	RealF rTravelTime;
	RealF rTime;
	RealF rForwardDelay;
	bool fInTimerSet;
	MoveableBaseData* mbData;

	Point3F ldistance;
	Point3F adistance;

	Point3F position;

	Point3F lvelocity;
	Point3F avelocity;

	virtual void updateServerMoveState(float rElapsedTime);
	virtual bool updateMovement();
	virtual void getPathID();
	virtual bool buildMovementVector(Int8 iCurWaypoint, Int8 state);
	virtual bool setMoveState(STATE stNew);
	virtual bool move(MOVEMENT move, Int8 iNewWaypoint);
	bool onSimTimerEvent(const SimTimerEvent* event);
	bool onSimMessageEvent(const SimMessageEvent* event);
	bool onSimTriggerEvent(const SimTriggerEvent*);
	bool onSimEditEvent(const SimEditEvent* event);
	virtual void onFirst();
	virtual void onLast();
	virtual void onWaypoint();

protected:
	MoveableBase();

	bool onAdd() override;
	bool processEvent(const SimEvent* event) override;
	void onRemove() override;
	bool initResources(GameBaseData* gbData) override;
	DWORD packUpdate(Net::GhostManager* gm, DWORD dwMask, BitStream* stream) override;
	void unpackUpdate(Net::GhostManager* gm, BitStream* stream) override;
	Error read(StreamIO& sio, int iVer, int iUsr) override;
	Error write(StreamIO& sio, int iVer, int iUsr) override;

public:
	virtual ~MoveableBase();
};
