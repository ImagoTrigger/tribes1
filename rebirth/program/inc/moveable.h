#pragma once

#include "MoveableBase.h"

class Moveable : public StaticBase
{
	typedef StaticBase Parent;

	DECLARE_PERSISTENT(Moveable);

public:
	static const size_t PathIdBits = 8;
	static const size_t WaypointBits = 4;

	struct MoveableData : public StaticBaseData
	{
	private:
		typedef StaticBaseData Parent;
	public:

		bool displace;
		bool blockForward;
		bool blockBackward;

		int sfxStart;
		int sfxStop;
		int sfxRun;
		int sfxBlocked;
		float speed;

		const char* side;

		MoveableData();
		void pack(BitStream* stream) override;
		void unpack(BitStream* stream) override;
	};

	enum State
	{
		Undefined,
		ForwardState,
		BackwardState,
		StopState
	};

public: //private:
	// TODO: Values
	enum
	{
		StateMask = LastMaskBit << 0,
		PathMask = LastMaskBit << 1,
		VelocityMask = LastMaskBit << 2,
		LastMaskBit = LastMaskBit << 3
	};

	MoveableData* data;
	State moveState;
	DWORD waypointStop;
	SimPathManager* spm;
	DWORD pathId;
	int cachedWaypoint;
	struct Position
	{
		SimTime time;
		int waypoint;
	} position, currentPos;
	SFX_HANDLE sound;
	bool runSound;
	bool blocked;
	int pathCount;
	SimTime pathTime;

	Vector3F lVector;
	Vector3F aVector;

	virtual void setPathId(int pid);
	virtual bool findPathId();
	virtual void setMoveState(State newState);
	virtual void updateMoveState(float dt);
	virtual void buildMovementVector();
	virtual bool updatePosition(bool force);


	virtual void onFirst();
	virtual void onLast();
	virtual void onWaypoint();
	virtual void onNewPath();

protected:

	bool onAdd() override;
	void onRemove() override;
	int getDatGroup() override;
	bool initResources(GameBaseData* gbData) override;
	void serverProcess(DWORD ct) override;
	void clientProcess(DWORD curTime) override;
	void onDeactivate() override;
	void onDamageStateChange(DamageState prevState) override;
	bool processBlocker(SimObject* obj) override;
	DWORD packUpdate(Net::GhostManager* gm, DWORD mask, BitStream* stream) override;
	void unpackUpdate(Net::GhostManager* gm, BitStream* stream) override;
	Error read(StreamIO & sio, int iVer, int iUsr) override;
	Error write(StreamIO& sio, int iVer, int iUsr) override;

public:
	Moveable();
	virtual ~Moveable();

	virtual bool moveToWaypoint(int waypoint);
	virtual void moveForward();
	virtual void moveBackward();
	virtual void stop();
	virtual const char* getMoveStateName();
	virtual float getWaypointPosition();

	virtual int getWaypointCount() const
	{
		return this->pathCount;
	}

	virtual bool setWaypoint(float waypoint);
};
