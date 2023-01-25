#pragma once

#include "m_point.h"
#include "Sound.h"
#include "GameBase.h"
#include "FearDcl.h"
#include "netCSDelegate.h"
#include "TeamGroup.h"
#include "FearHudCmdObj.h"

class TeamGroup;
class PlayerPSC;
class ObserverCamera;
class AIObj;

namespace Net
{
	class GhostManager;
	class EventManager;
	class PacketStream;
}

// TODO: Guess ..
static const size_t MAX_MSG_LENGTH = 256;

// TODO: Find correct size.
static const size_t MaxScoreString = 256;

//	TODO: Guess this is right, Tribes UI won't let you create a server with more players than this.
const size_t MaxClients = 128;

// TODO: Guess this is the same as MaxClients?
static const size_t NUM_MUTED_DWORDS = MaxClients;

// TODO: Ensure is correct.
static const size_t ClientIdSize = 7;//12;

// TODO: Ensure this is correct. See FearPlayerPSC line 884
static const size_t TeamIdSize = 3;


class PlayerManager : public SimObject
{
	// TODO: SimObject guess.
	typedef SimObject Parent;

	friend class FearCSDelegate;


	

	// TODO: Real value
	static const size_t MaxVoiceFileLen = 31;

public:
	// TODO: Max teams 9? or is it 8 with an implicit + 1 for observer team?
	static const size_t MaxTeams = 9;

	enum Gender
	{
		Female,
		Male
	};

	// TODO: name and values correct?
	enum CmdStatus
	{
		CMD_NONE,
		CMD_RECEIVED,
		CMD_ACKNOWLEDGED
	};

	struct ClientRep;

	struct BaseRep
	{


		int id;
		int team;
		StringTableEntry name;
		StringTableEntry skinBase;
		char scoreString[MaxScoreString];
		int scoreSortValue;

		int loginId;
		bool selected;

		GameBase* ownedObject;

		int commandStatus;
		int curCommander;
		int curCommand;
		int lastObjectiveSequence;
		int lastScoreSequence;
		int scoreSequence;
		int lastCommandSequence;
		int curCommandSequence;

		bool dataFinished;

		int commanderId;
		ClientRep* commander;
		ClientRep* firstPeon;
		ClientRep* nextPeon;

		int curGuiMode;
		bool isBaseRepType;
		int ping;
		GameBase* controlObject;
		Vector3F position;
		AIObj* ai;

		bool sendScores;

		const char* voiceBase;

		int gender;
		bool expanded;
		const char* lastCMDMessage;

		int listenChannels;

		ClientRep* nextClient;

		virtual bool isClientRep() const
		{
			return false;
		}

		void setGenericDefaults(StringTableEntry playerName, StringTableEntry voice, StringTableEntry skin, bool male, AIObj* otherControl);
	};

	// TODO: Find correct base?
	struct ClientRep : public BaseRep
	{
	public: //private:
		

	public:
		SFX_HANDLE chatSfxHandle = NULL;
		Net::GhostManager* ghostManager;
		Net::EventManager* eventManager;
		Net::PacketStream* packetStream;
		PlayerPSC* playerPSC;		

		
		
		
		
			
		ObserverCamera* observerCamera;
		
		
		
		float packetLoss;
		

		DWORD mutedPlayerList[NUM_MUTED_DWORDS];
		bool mutedMe;




		int curCommandTarget;

		Point2I wayPoint;

		

		const char* curCommandString;
		Int32 commandLevel;

		bool isClientRep() const override
		{
			return true;
		}

		void clean();
	};

	// TODO: Find correct base?
	struct TeamRep : public BaseRep
	{		
	public: //private:
		// TODO: Figure out name
		struct Obj
		{
			int seqNum;
			// TODO: Figure out Length
			char text[256];
		};


	public:
		int energy;
		ClientRep* firstCommander;
		
		Obj objectives[MAX_NUM_OBJECTIVES];

	};

public: //private:

	ClientRep clientList[MaxClients];
		
	TeamRep teamList[MaxTeams];

	int curScoreSequence;
	ClientRep* clientLink;
	BaseRep* baseRepLink;

	ClientRep* clientFreeList;

	

	
	char teamScoreHeading[MaxScoreString];
	char clientScoreHeading[MaxScoreString];
	int numClients;
	int numBaseReps;
	int curLoginId;
	int numTeams;
	
	const char* lastCMDMessage;
	
	bool isServer;

	int curCommandSequence;
	int curObjectiveSequence;


	explicit PlayerManager(bool onServer);

public:
	static PlayerManager* get(SimManager* simManager)
	{
		return dynamic_cast<PlayerManager*>(simManager->findObject(PlayerManagerId));
	}

	virtual ~PlayerManager();

	virtual void setTeam(int playerId, int teamId);
	virtual void buildCommandTrees();
	virtual void teamAdded(int teamId);
	virtual TeamGroup* getTeamGroup(int teamId);
	virtual void sendPingPackets();
	virtual void setDisplayScores(int clientId, bool display);
	virtual void setClientSkin(int clientId, const char* in_skin);
	virtual void setTeamScore(int teamId, const char* scoreString, int sortValue);
	virtual void setClientScoreHeading(const char* heading);
	virtual void setTeamScoreHeading(const char* heading);
	virtual void setClientScore(int clientId, const char* scoreString, int sortValue);
	virtual void removeClient(ClientRep* cr);
	virtual void clientDropped(int playerId);
	virtual void clientGuiModeChanged(int clientId, int newGuiMode, int oldGuiMode);
	virtual void clearTeamObjectives(int teamId);
	virtual void setTeamObjective(int teamId, int objNum, const char* text);
	// TODO: Default -1?
	virtual void issueCommand(int cmdrId, int targId, int commandIcon, const char* commandString, Point2I& wayPoint, int objectIndex = -1);
	virtual bool isInCommandChain(int peonId, int cmdrId);
	virtual void setCommander(ClientRep* peon, ClientRep* cmdr);
	virtual void selectCommander(int peonId, int cmdrId);
	virtual bool commandStatusReport(int peonId, int status, const char* message);
	virtual void messageClient(int playerId, int srcClientId, int messageType, const char* message);
	virtual void mute(int playerId, int mutePlayerId, bool on_off);
	virtual void serverPlayVoice(int clientId, const char* voiceString);
	bool processEvent(const SimEvent* event) override;
	virtual void _cdecl printf(int msgType, const char* fmt,...);
	virtual void missionReset();
	virtual void reset();
	virtual void ghostAlwaysDone(int playerId);
	virtual TeamRep* findTeam(int id);
	virtual TeamRep* findTeam(const char* name);
	virtual ClientRep* findClient(int id);
	virtual ClientRep* findBaseRep(int id);
	virtual const char* getPlayerSkinBase(int clientId);
	virtual const char* getTeamSkinBase(int teamId);

	virtual int getNumBaseReps() const
	{
		return this->numBaseReps;
	}	
	
	virtual BaseRep* getBaseRepList()
	{
		return this->baseRepLink;
	}

	virtual int getNumClients() const
	{
		return this->numClients;
	}

	virtual ClientRep* getClientList()
	{
		return this->clientLink;
	}

	virtual int getNumTeams() const
	{
		return this->numTeams;
	}

	virtual void clientAdded(const char* name, const char* voiceBase, StringTableEntry skinBase, bool gender, AIObj* = nullptr);

	virtual int getFreeId() const
	{
		return clientFreeList[0].id;
	}
};
