#pragma once

#include "tribesShadowRenderImage.h"
//#include "shapebase.h"
#include "simMoveObj.h"
#include "simTSShape.h"
#include "g_bitmap.h"
#include "console.h"

struct ProjectileDataType;
class PlayerMove;
class CameraInfo;
class CommandStatus;

class GameBase : public SimMovement
{
	// TODO: SimMoveObject Guess
	typedef SimMovement Parent;

	friend class SensorManager;
	friend class PlayerPSC;
	friend class FearGame;

protected:
	// TODO: Values
	enum
	{
		BaseStateMask = 1 << 0,
		InitialUpdate = 1 << 1,
		LastMaskBit = 1 << 2
	};

public:
	class GameBaseData
	{
		friend class GameBase;
		friend class DataBlockManager;
		friend class FearDynamicDataPlugin;

		void* pluginClass;
		int dbmIndex;
		const char* dbmDatFileName;
		GameBaseData* dbmNextHash;

	public:
		const char* className;
		bool visibleToSensor;
		int mapFilter;
		const char* description;
		const char* mapIcon;
		Resource<GFXBitmap> iconBmp[2];

		virtual void pack(BitStream* stream);
		virtual void unpack(BitStream* stream);
		GameBaseData();
		virtual bool preload(ResourceManager * rm, bool server, char errorBuffer[256]);
	};

	virtual const Vector3F& getCompassRotation()
	{
		return Vector3F(1,0,0);
	}
public:

	// TODO: Get real value
	static const BYTE SensorPingedBase = 1 << 0;

	// TODO: Get real value
	static const BYTE PingStatusSupressed = 1 << 1;
	// TODO: Real value
	static const BYTE PingStatusClear = 1 << 6;
	// TODO: Get real value
	static const BYTE PingStatusOn = 1 << 2;

	// TODO: Get real value
	static const BYTE NeverVisBase = 1 << 3;

	// TODO: Get real value
	static const BYTE TeamVisBase = 1 << 4;

	// TODO: Get real value
	static const BYTE AlwaysVisBase = 1 << 5;

	static const size_t TeamIdBits = 4;




protected:
	struct CommandStatus
	{
		float damageLevel;
		bool active;
	};

	// TODO Real values
	//enum
	//{
	//	BaseStateMask = BIT(24),
	//	InitialUpdate = BIT(31)
	//};

	//enum NetFlag
	//{
	//	FirstNetFlagGoesHere = Parent::MaxNetFlagBit,
	//	MaxNetFlagBit = FirstNetFlagGoesHere << 1
	//};

public: //private:
	class Timer
	{
		class Entry
		{
		public:
			virtual ~Entry();

			// TODO: Order check.
			SimObject* object;
			SimTime collisionTime;
		};

		class FreeList
		{
			Timer* nextFree;

		public:
			FreeList();
			virtual ~FreeList();
			void push(Timer* obj);
			Timer* pop();
		};

		// TODO: Get real value
		static const size_t ReservedSize = 32;

		static FreeList freeList;

		Vector<Entry> entryList;
		Timer* nextFree;
		SimTime maxTime;

		Timer();


		Entry* find(SimObject* obj, SimTime time);



	public:
		virtual ~Timer();
		static Timer* newTimer();

		void free();
		bool allExpired(SimTime time);
		bool isCollisionExpired(SimObject* obj, SimTime time);
	};


public:
	static float upFov;
	static float upDistance;
	static float upVelocity;
	static float upSkips;
	static float upOwnership;
	static float upInterest;

public: //private:

	int teamId;
	int ownerId;
	int ctrlClientId;
	int ownerClientId;
	int lastOwnerClientId;
	int powerCount;
	bool powerGenerator;



	Timer* timer;
	DWORD sensorInfoBits;
	GameBaseData* data;

	const char* mapName;







	virtual int getDatGroup();






	virtual void serverProcess(DWORD curTime);
	virtual void serverUpdateMove(PlayerMove * moves, int moveCount);
	virtual void setPlayerControl(bool);
	virtual const char* getScriptDefaultClass();




	virtual bool cameraZoomAndCrosshairsEnabled();

	virtual void onCollisionNotify(GameBase* obj);

	virtual SimObject* getTeamObject(const char* objectName);
	virtual SimGroup* getTeamGroup();
	virtual void updateTeamId();
	virtual void updatePowerCount();
	virtual void updatePowerClients(SimGroup* group, bool power);

	virtual void forcePowerState(bool on);
	virtual void onPowerStateChange(GameBase* generator);



	virtual void scriptOnInit();

	virtual void writePacketData(BitStream*);
	virtual void readPacketData(BitStream*);





	virtual bool getCommandStatus(CommandStatus * status);



	virtual bool getImageEnhanceable();
	virtual bool isCloaked();
	virtual bool isJammingSensor();

public:

	virtual BYTE getSensorPinged();
	virtual void setSensorPinged(BYTE fPinged);


protected:
	GameBase();

	const char* datFileName;
	int datFileId;
	int lastAnimateTime;
	int lastProcessTime;
public:
	int sensorKey;
protected:
	float fov;

	virtual bool loadDatFile();

	virtual void scriptOnAdd();
	virtual void scriptOnRemove();
	virtual void clientProcess(DWORD curTime);

	virtual void setAlwaysVisibleToTeam(int iTeamID, bool fVisible);
	virtual bool getAlwaysVisibleToTeam(int iTeamID);
	virtual void setNeverVisibleToTeam(int iTeamID, bool fVisible);
	virtual bool getNeverVisibleToTeam(int iTeamID);
	virtual void setVisibleToTeam(int iTeamID, bool fVisible);


	virtual void scriptOnCollision(GameBase* obj);


	virtual bool initResources(GameBaseData* ptr);
	bool onAdd() override;
	void onRemove() override;
	bool processArguments(int argc, const char** argv) override;
	void onGroupAdd() override;
	void onGroupRemove() override;

	void buildScopeAndCameraInfo(Net::GhostManager* cr, CameraInfo* camInfo) override;
	float getUpdatePriority(CameraInfo * camInfo, DWORD updateMask, int updateSkips) override;
	DWORD packUpdate(Net::GhostManager*, DWORD mask, BitStream* stream) override;
	void unpackUpdate(Net::GhostManager*, BitStream* stream) override;
	void inspectRead(Inspect* inspector) override;
	void inspectWrite(Inspect* inspector) override;
	Error read(StreamIO& sio, int, int) override;
	Error write(StreamIO& sio, int, int) override;




	virtual float validateEyePoint(TMat3F* trans, float camDist);

	void packDatFile(BitStream* stream);
	void unpackDatFile(BitStream* stream);




	virtual void updateTimers();





	virtual SimObjectId getOwnerId() const
	{
		return this->ownerId;
	}

	virtual void setOwnerId(const SimObjectId i)
	{
		this->ownerId = i;
	}


	virtual bool isControlable() const
	{
		return false;
	}

public:
	virtual GameBaseData* getDatPtr() const
	{
		return this->data;
	}

protected:
	virtual bool mousePitch() const
	{
		if(Console->getBoolVariable("$pref::freeLookAlwaysOn", true)) // TODO: Default true if not present?
		{
			return true;
		}
		else
		{
			// TODO: If freeLookAlwaysOn is off, need to check if actively freelooking (E.g. F key pressed).
			return false;
		}
	}

public: //private:



public:
	virtual ~GameBase();

	static void initPersistFields();

	virtual bool getWeaponAmmoType(ProjectileDataType& out_rPrimary, ProjectileDataType& out_rSecondary)
	{
		return false;
	}


	virtual int getDatFileId() const
	{
		return this->datFileId;
	}



	virtual void setFov(const float f)
	{
		this->fov = f;
	}

	virtual DWORD getLastProcessTime()
	{
		return this->lastProcessTime;
	}

	virtual void setLastProcessTime(const DWORD p)
	{
		this->lastProcessTime = p;
	}


	virtual void setOwnerClient(int clientId);
	virtual void setControlClient(int clientId);

	virtual void generatePower(bool power);

	virtual int getTeam() const
	{
		return this->teamId;
	}

	virtual bool isGenerator() const
	{
		return this->powerGenerator;
	}

	virtual bool isPowered() const
	{
		return this->powerCount > 0; // || isGenerator()?
	}

	virtual	int getPowerCount() const
	{
		return this->powerCount;
	}

	virtual bool mountRender() const
	{
		return true;
	}

	virtual int getMountPose() const
	{
		return -1;
	}

	virtual const Point3F& getLeadVelocity()
	{
		return this->lVelocity;
	}

	bool processEvent(const SimEvent* event) override;
	static void throwObject(GameBase* object, float speed, bool careless);
	virtual const char* scriptName(const char* callback);

	virtual bool isActive();
	virtual bool setActive(bool a);

	virtual void setName(const char* name);

	virtual const char* getDatFileName() const
	{
		return this->datFileName;
	}

	virtual void setDatFileName(const char* in_name);

	virtual const char* scriptThis();

	virtual bool getMuzzleTransform(int, TMat3F* mat);

	virtual bool getVisibleToTeam(int iTeamID);
	virtual float getDamageFlash();
	virtual float getEnergyLevel();
	virtual float getDamageLevel();

	virtual void getObjectMountTransform(int, TMat3F* mat);
	virtual void getCameraTransform(float, TMat3F* mat);

	virtual const TMat3F& getEyeTransform()
	{
		throw std::exception("Should never get here? Add Pure virtual specifier?");
	}
	virtual bool getTarget(Point3F* const targetPoint, int* team) const
	{
		throw std::exception("Should never get here? Add Pure virtual specifier?");
	}

	virtual void getThrowVector(Point3F* pos, Point3F* vec);
	virtual int getControlClient();
	virtual int getLastOwnerClient();
	virtual int getOwnerClient();

	virtual float getHaze(const Point3F& cameraPos);

	virtual void setTeam(int _team);
};

class FearRenderImage : public TribesShadowRenderImage
{
protected:
	Box3F m_containerBox;
	bool m_attenuateSun;
	ColorF m_attenuationColor;
	float m_attenuationFactor;

public: //private:
	virtual void renderBoundingBox(TSRenderContext& rc);
	void render(TSRenderContext& rc) override;
	virtual void updateSunOverride(const bool in_attenuate, const float in_factor, const ColorF& in_color);
};
