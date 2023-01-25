#pragma once

#include "m_point.h"

namespace SimGui
{
	class playDelegate;
}

namespace FearGui
{
	class TSCommander;
	class CMDObserve;
	class ServerListCtrl;
}

namespace Net
{
	class PacketStream;
}

class SimManager;
class ResourceManager;

class FearCSDelegate;
class DataBlockManager;

class Player;
class PlayerManager;
class PlayerPSC;

class WorldGlobals
{
public:
	SimManager* manager;
	ResourceManager* resManager;
	DWORD currentTime;
	DWORD timeBase;
	DWORD lastTime;
	double clockTime;

	FearCSDelegate* csDelegate;
	Net::PacketStream* packetStream;
	PlayerPSC* psc;
	DataBlockManager* dbm;
	bool editMode;

	int curCommand;
	Point2F missionCenterPos;
	Point2F wayPoint;
	Point2F missionCenterExt;

	PlayerManager* playerManager;

	Player* player;

	SimGui::playDelegate* playDelegate;
	FearGui::TSCommander* commandTS;
	FearGui::CMDObserve* cmdObserve;
	FearGui::ServerListCtrl* gameServerList;
	
	DWORD predictForwardTime;
	DWORD interpolateTime;

	WorldGlobals() :
		manager(nullptr),
		resManager(nullptr),
		currentTime(GetTickCount()),
		timeBase(GetTickCount()),
		lastTime(0),
		clockTime(0),
		csDelegate(nullptr),
		packetStream(nullptr),
		psc(nullptr),
		dbm(nullptr),
		editMode(false),
		curCommand(0),
		playerManager(nullptr),
		player(nullptr),
		playDelegate(nullptr),
		commandTS(nullptr),
		cmdObserve(nullptr),
		gameServerList(nullptr),
		predictForwardTime(0),
		interpolateTime(0)
	{
	}
};

extern WorldGlobals cg;
extern WorldGlobals sg;
extern WorldGlobals* wg;
