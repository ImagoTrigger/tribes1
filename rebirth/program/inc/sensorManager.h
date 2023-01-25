#pragma once

#include "Player.h"
#include "Sensor.h"
#include "car.h"

extern bool gSensorNetworkEnabled;

class Sensor;

struct TargetNameEvent : public SimEvent
{
	typedef SimEvent Parent;

	DECLARE_PERSISTENT(TargetNameEvent);

	int targId;
	const char* name;

	TargetNameEvent();
	void pack(SimManager* manager, Net::PacketStream* ps, BitStream* bs) override;
	void unpack(SimManager* manager, Net::PacketStream* ps, BitStream* bs) override;
};

class SensorManager : public SimContainer
{
	// TODO: Guess SimContainer
	typedef SimContainer Parent;

	friend class GameBase;
	friend class Sensor;
	friend class PlayerPSC;
	friend class Player;

	// TODO: Get real size.
	static const size_t MaxTargets = 127;

	// TODO: Get real value.
	static const size_t MaxTargetsMask = 0x7F;

	int targetCount;
	int lastPinged;
	int lastPlayer;

	Player* playerSupressorListHead;
	Sensor supressionListHead;
	Sensor sensorListHeads[PlayerManager::MaxTeams];
	
	const char* targetNames[MaxTargets];

	void removeTarget(int targId);
	void changeTargetName(int key, const char* name);
	
	int addTarget(GameBase* targ, const char* name);
	bool onSimTimerEvent(const SimTimerEvent*);
	void testObject(GameBase* obj);

protected:
	void addPlayerSupressor(Player* pl);
	bool onAdd() override;
	void addSensor(Sensor* pSensor);
	bool processEvent(const SimEvent* event) override;

public:
	SensorManager();
	virtual ~SensorManager();

	GameBase* targets[MaxTargets + 1];

	void newClient(int managerId);
};
