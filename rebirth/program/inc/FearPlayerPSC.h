#pragma once

#include "netPacketStream.h"
#include "Console.h"
#include "SimMovement.h"
#include "Player.h"
#include "PlayerManager.h"
#include "simAction.h"
#include "Item.h"

class PlayerPSC : public Net::PacketStreamClient
{
	typedef PacketStreamClient Parent;

	friend class FearGame;
	friend class FearCSDelegate;
	friend class Player;

	static float playerFov;
	static float sniperFov;
	static float zoomSpeed;

public:
	// TODO: Size
	static const size_t ItemShoppingListWords = 4;

public: //private:
	struct InvUpdate
	{
		InvUpdate* link;
		int item;
		int delta;
	};

	struct PacketHead
	{
		bool resetItems;
		DWORD xorShoppingList[ItemShoppingListWords];
		DWORD xorBuyList[ItemShoppingListWords];
		int xorVisibleList[8];

		InvUpdate* invUpdates;
	};

	struct
	{
		PacketHead* alloc()
		{
			//throw std::exception("NYI");
			return (PacketHead*)malloc(sizeof(PacketHead));
		}

		void free(PacketHead* mem)
		{
			//throw std::exception("NYI");
			return ::free(mem);
		}
	} phLL;

	struct
	{
		InvUpdate* alloc()
		{
			return (InvUpdate*)malloc(sizeof(InvUpdate));
			//throw std::exception("NYI");
		}

		void free(InvUpdate* mem)
		{
			return ::free(mem);
			//throw std::exception("NYI");
		}
	} invLL;

	DWORD shoppingList[ItemShoppingListWords];
	DWORD buyList[ItemShoppingListWords];
	DWORD clientShoppingList[ItemShoppingListWords];
	DWORD clientBuyList[ItemShoppingListWords];

	int triggerCount;
	int prevTriggerCount;
	bool limitCommandBandwidth;
	bool firstPerson;
	float camDist;

	float yawSpeed;
	float pitchSpeed;
	float turnLeftSpeed;
	float turnRightSpeed;
	float lookUpSpeed;
	float lookDownSpeed;
	int lastSensorSeq;
	int lastSent;

	GameBase* controlObject;
	Player* controlPlayer;
	bool isServer;
	bool resetItems;
	PlayerManager* playerManager;
	int lastPlayerMove;
	int firstMoveSeq;

	float targetFov;
	float fovStartTime;
	float fovTargetTime;
	float viewPitch;

	bool fInObserverMode;
	bool fInEditMode;

	float damageFlash;

public:
	// TODO: Enum order
	enum
	{
		InitialGuiMode,
		PlayGuiMode,
		CommandGuiMode,
		VictoryGuiMode,
		InventoryGuiMode,
		ObjectiveGuiMode,
		LobbyGuiMode,
		NumGuiModes
	};

public: //private:
	int curGuiMode;

	int itemTypeCount[Player::MaxItemTypes];

	int visibleList[8];
	const char* targetNames[128];

	// Previous moves vector?
	Vector<PlayerMove> pmvec;
	Vector<PlayerMove> moves;
	PlayerMove curMove;

	float startFov;

	Resource<SimActionMap> eventMap;

	static const char* validateFov(CMDConsole *, int id, int argc, const char * argv[]);

	explicit PlayerPSC(bool in_isServer);

	virtual ~PlayerPSC();

	virtual void getFovVars(float* pFov, float* pZoomFov, float* pTargetFov, DWORD* pStartTime, DWORD* pFovTime);



	virtual void clientCollectInput(DWORD startTime, DWORD endTime);

	bool onSimTimerEvent(const SimTimerEvent*);
	virtual PlayerMove* getCurrentMove();
	virtual const char* getTargetName(int sensorKey);


	virtual bool processAction(int action, float eventValue, int iDevice);

	bool onSimGainFocusEvent(const SimGainFocusEvent*);
	bool onSimLoseFocusEvent(const SimLoseFocusEvent*);
	virtual void toggleObserverCamera();
	virtual void toggleEditCamera();


	virtual float getFarPlane();

	virtual bool isFirstPerson() const
	{
		return this->firstPerson;
	}


public://protected:
	void onDeleteNotify(SimObject* obj) override;
	bool onAdd() override;
	bool processEvent(const SimEvent* event) override;
	void processRecorderStream(StreamIO* sio, DWORD) override;
	void notifyPlaybackOver() override;
	bool processQuery(SimQuery* query) override;
	bool writePacket(BitStream* bstream, DWORD& key) override;
	void readPacket(BitStream* bstream, DWORD currentTime) override;
	void packetDropped(DWORD key) override;
	void packetReceived(DWORD key) override;

public:
	bool onSimActionEvent(const SimActionEvent* event);

	virtual bool isItemBuyOn(int type);
	// TODO: Default -1?
	virtual void clearItemBuyList(int type = -1);
	// TODO: Default -1?
	virtual void setItemBuyList(int type = -1);
	virtual bool isItemShoppingOn(int type);
	// TODO: Default -1?
	virtual void clearItemShoppingList(int type = -1);
	// TODO: Default -1?
	virtual void setItemShoppingList(int type = -1);

	virtual void useItem(int typeId);

	virtual int itemCount(int item);

	virtual PlayerMove* getClientMove(DWORD time);

	virtual float getDamageLevel();
	virtual float getEnergyLevel();

	virtual GameBase* getControlObject() const
	{
		return this->controlObject;
	}

	virtual int getCurrentGuiMode() const
	{
		return this->curGuiMode;
	}

	virtual void setCurrentGuiMode(const int value)
	{
		this->curGuiMode = value;
	}

	virtual void setControlObject(GameBase* obj);

	virtual void setCommandBandLimit(const bool value)
	{
		this->limitCommandBandwidth = value;
	}

	// TODO:
	virtual bool playerVisible(const int id)
	{
		return true;
	}
};
