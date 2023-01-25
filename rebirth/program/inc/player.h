#pragma once

#include "ShapeBase.h"
#include "simLightGrp.h"
#include "projectileFactory.h"
#include "Planet.h"
#include "playerCollision.h"
#include "Item.h"

class PlayerMove
{
public:
	int forwardAction;
	int backwardAction;
	int leftAction;
	int rightAction;
	bool jetting;
	bool jumpAction;
	bool crouching;
	float turnRot;
	float pitch;
	bool trigger;
	int useItem;

	void write(BitStream* bstream, bool full = true, PlayerMove* prev = nullptr);
	void read(BitStream* bstream, bool full = true, PlayerMove* prev = nullptr);

	PlayerMove();

	void reset();
};

class Player : public ShapeBase
{
	friend class PlayerPSC;
	friend class SensorManager;
	friend class FearDynamicDataPlugin;
	friend class AIObj;

	DECLARE_PERSISTENT(Player);

	struct SurfaceInfo
	{
		CollisionSurface* surface;
		SimObject* object;
		float stepHeight;
		float verticalDot;
		Point3F normal;
	};

	typedef Vector<SurfaceInfo> SurfaceInfoList;


public:

	virtual bool isItemFiring(int imageSlot);
	virtual bool isItemMounted(int type);
	virtual int getItemTeam(int imageSlot);
	virtual const char* scriptItemName(int type, const char* callback);
	virtual const char* scriptItemThis(int type);
	virtual const char* scriptThis() override;
	virtual void scriptOnUseItem(int type);
	virtual void scriptOnDropItem(int type);
	virtual void scriptOnDeployItem(int type, const Point3F& pos);
	virtual void scriptOnMountItem(int type);
	virtual void scriptOnUnmountItem(int type);
	virtual void packItemImages(BitStream* stream, DWORD mask);
	virtual void unpackItemImages(BitStream* stream);
	static Item::ItemData* getItemData(int typeId);
	virtual const char* getItemName(int typeId);
	virtual const char* getImageName(int typeId);

	virtual void calcImagePullIn();
	virtual bool getImageTransform(int imageSlot, TMat3F* mat);
	virtual bool getMuzzleTransform(int imageSlot, TMat3F* mat) override;
	virtual const char* scriptImageName(int imageSlot, const char* callback);
	virtual void updateImageMass();
	// TODO: Default -1?
	virtual void setImageType(int imageSlot, int typeId, int team = -1);
	virtual void resetImageSlot(int imageSlot);
	virtual SimRenderImage* getImage(int imageSlot, TSRenderContext* rc);

	virtual void updateImageAnimation(int imageSlot, float dt);
	virtual void updateImageState(int imageSlot, float dt);
	virtual void setImageSound(int imageSlot, int soundTag);
	virtual void scriptOnNoAmmo(int imageSlot);
	virtual void startImageFire(int imageSlot);
	virtual void updateImageFire(int imageSlot);
	virtual void stopImageFire(int imageSlot);
	virtual void fireImageProjectile(int imageSlot);
	virtual TSLight* getImageLight(int imageSlot);
	void readPacketData(BitStream* bstream);
	void writePacketData(BitStream* bstream);

	void ghostSetMove(PlayerMove* move, Point3F& newPos, Point3F& newVel, bool cont, float newRot, float newPitch, int skipCount, bool noInterp);
	void setPlayerControl(bool control);
	void fallToGround(float interval);
	void stepDelta(float amt);
	void clientProcess(DWORD curTime);
	int getFootPrint(bool isRight);
	void serverProcess(DWORD curTime);
	void updateMove(PlayerMove* curMove, bool server);

	void onDisplacement(SimMovement* displacer, const Point3F& delta);
	bool processCollision(SimMovementInfo* info);
	bool stepSurface(SimMovementInfo* info, SurfaceInfoList& surfaceList);
	void pickSurfaceType(SurfaceInfoList & surfaceList);
	bool collideSurface(int index, SurfaceInfoList& surfaceList);
	DWORD packUpdate(Net::GhostManager* gm, DWORD mask, BitStream* stream);
	void unpackUpdate(Net::GhostManager* gm, BitStream* stream);

	// TODO: Guess ShapeBase?
	typedef ShapeBase Parent;

	// TODO: Get real value
	static const size_t MaxItemImages = 8;

	// TODO Order maybe mirror with Item::ItemData
	enum LightType
	{
		NoLight,
		ConstantLight,
		PulsingLight,
		WeaponFireLight
	};

	enum
	{
		root,
		run,
		runback,
		sideleft1,
		sideleft2,
		jumpstand,
		jumprun,
		crouchroot1,
		crouchroot2,
		crouchroot3,
		crouchforward1,
		crouchforward2,
		crouchsideleft1,
		crouchsideleft2,
		fall,
		landing,
		landing2,
		tumbleloop,
		tumbleend,
		jet,
		pdaaccess,
		Throw,
		flyerroot,
		apcroot,
		apcpilot,
		crouchdie,
		diechest,
		diehead,
		diegrabback,
		dierightside,
		dieleftside,
		dielegleft,
		dielegright,
		dieblownback,
		diespin,
		dieforward,
		dieforwardkneel,
		dieback,
		signoverhere,
		signpoint,
		signretreat,
		signstop,
		signsalut,
		celebration1,
		celebration2,
		celebration3,
		taunt1,
		taunt2,
		posekneel,
		posestand,
		wave,
		NUM_ANIMS
	};

	enum
	{
		ANIM_PLAYER_FIRST = signoverhere,
		ANIM_PLAYER_LAST = wave,
		ANIM_MOVE_FIRST = run,
		ANIM_MOVE_LAST = sideleft2,
		ANIM_CROUCH_MOVE_FIRST = crouchforward1,
		ANIM_CROUCH_MOVE_LAST = crouchsideleft2,
		ANIM_IDLE = root,
		ANIM_JUMPRUN = jumprun,
		ANIM_CROUCH = crouchroot1,
		ANIM_CROUCH_IDLE = crouchroot2,
		ANIM_FALL = fall,
		ANIM_LAND = landing,
		ANIM_JET = jet,
		ANIM_PDA = pdaaccess,
		ANIM_FLIER = flyerroot,
		ANIM_APC_RIDE = apcroot,
		ANIM_STAND = root,
		ANIM_TUMBLE_LOOP = tumbleloop,
		ANIM_DIE_GRAB_BACK = diegrabback,
	};

public:
	static const size_t NUM_FOOTSOUNDS = TS::Material::SurfaceType::PackedEarthType + 1;

	// TODO: Real value
	static const size_t ItemTypeBits = 8;

	static const size_t MaxImageSlots = 8;

	struct AnimData
	{
		const char* name;
		int soundTag;
		int direction;
		// TODO: Values
		enum ViewFlags
		{
			FirstPerson = BIT(0),
			ChaseCam = BIT(1),
			ThirdPerson = BIT(2),
			HoldPose = BIT(3)
		} viewFlags;
		int priority;
	};

	enum
	{
		SingleShot,
		Spinning,
		Sustained,
		DiscLauncher
	};


	struct ItemImageData : public GameBaseData
	{
		// TODO: Guess GameBaseData, maybe ItemData?
		typedef GameBaseData Parent;

		StringTableEntry shapeFile;
		int mountPoint;
		Point3F mountOffset;
		Point3F mountRotation;
		bool firstPerson;
		bool accuFire;

		int weaponType;
		int ammoType;
		SimTime activateTime;
		SimTime fireTime;
		SimTime reloadTime;
		SimTime spinUpTime;
		SimTime spinDownTime;
		ProjectileDataType projectile;
		float minEnergy;
		float maxEnergy;
		float mass;
		int lightType;
		SimTime lightTime;
		float lightRadius;
		Point3F lightColor;
		SimTag sfxActivateTag;
		SimTag sfxFireTag;
		SimTag sfxReadyTag;
		SimTag sfxReloadTag;
		SimTag sfxSpinUpTag;
		SimTag sfxSpinDownTag;

		int activationSequence;
		int ambientSequence;
		int spinSequence;
		int fireSequence;
		int reloadSequence;
		int noammoSequence;
		int readySequence;

		Resource<TSShape> shape;

		ItemImageData();
		bool preload(ResourceManager * rm, bool server, char errorBuffer[256]) override;
		void pack(BitStream* stream) override;
		void unpack(BitStream* stream) override;
	};

	struct PlayerData : public ShapeBaseData
	{
	private:
		typedef ShapeBaseData Parent;

	public:

		float groundForce;
		float groundTraction;
		float maxJetForwardVelocity;
		float maxJetSideForceFactor;
		float minJetEnergy;
		float jetEnergyDrain;
		float jumpSurfaceMinDot;
		float jumpImpulse;

		float minDamageSpeed;
		float damageScale;

		float boxNormalHeadPercentage;
		float boxNormalTorsoPercentage;
		float boxCrouchHeadPercentage;
		float boxCrouchTorsoPercentage;

		float boxHeadLeftPercentage;
		float boxHeadRightPercentage;
		float boxHeadFrontPercentage;
		float boxHeadBackPercentage;

		float boxCrouchHeight;
		float boxNormalHeight;

		const char* flameShapeName;
		bool canCrouch;

		AnimData animData[NUM_ANIMS];

		float maxForwardSpeed;
		float maxBackwardSpeed;
		float maxSideSpeed;
		float mass;
		float drag;
		float density;
		float jetForce;
		int rFootSounds[NUM_FOOTSOUNDS];
		int lFootSounds[NUM_FOOTSOUNDS];
		int footPrints[2];
		int jetSound;
		float boxWidth;
		float boxDepth;

		PlayerData();
		void pack(BitStream* stream);
		void unpack(BitStream* stream);
	};

	static int getItemType(const char* name);
public: //private:

	// TODO: find size
	static const size_t MaxItemTypes = 256;

	// TODO: find size
	static const size_t ItemImageMaskBits = 3;

	// TODO: values
	enum
	{
		AnimationMask = LastMaskBit,
		MountMask = LastMaskBit << 1,
		VisItemMask = LastMaskBit << 2,
		NoInterpMask = LastMaskBit << 3,
		LastMaskBit = LastMaskBit << 4
	};

	enum MountPoint
	{
		PrimaryMount,
		SecondaryMount,
		BackpackMount,
		JetExhaust,
		MaxMountPoints
	};

	int mountNode[MaxMountPoints];
	float deltaPitch;
	float deltaTurn;
	Point3F deltaPos;
	float forwardAxisMovement;
	float sideAxisMovement;

	struct ItemTypeEntry
	{
		int count;
		int imageSlot;
		ItemTypeEntry();
	};

	ItemTypeEntry itemTypeList[MaxItemTypes];

	struct ItemImageEntry
	{
		FearRenderImage image;

		// TODO: values / order
		enum State
		{
			Reset,
			Idle,
			NoAmmo,
			Activate,
			Ready,
			Fire,
			Reload,
			SpinUp,
			SpinDown,
			Deactivate
		} state;
		int typeId;
		int imageId;
		int nextId;
		int teamId;
		int nextTeam;
		SFX_HANDLE animSound;
		SFX_HANDLE spinSound;
		bool animLoopingSound;
		SimTime delayTime;
		bool ammo;
		bool triggerDown;
		int fireCount;
		SimTime lightStart;
		Projectile* pProjectile;
		int muzzleNode;
		TSLight light;

		Resource<TSShape> shapeRes;

		TSShapeInstance::Thread* ambientThread;
		TSShapeInstance::Thread* animThread;
		TSShapeInstance::Thread* spinThread;
		Resource<TSMaterialList> materialList;

		ItemImageEntry();

		virtual ~ItemImageEntry();
	};

	struct
	{
		float dist;
		Point3F dir;
		bool hasOffset;
	} offsetList[NUM_ANIMS];



	ItemImageEntry itemImageList[MaxImageSlots];

	PlayerCollisionImage collisionImage;

	Player* prevSup;
	Player* nextSup;


	PlayerMove lastPlayerMove;


	static const DWORD csm_respawnEffectTime;

	TSShapeInstance::Thread* viewThread;
	DWORD m_respawnStartTime;
	DWORD m_respawnEndTime;
	int currentAnimation;
	bool lastFreeLook;

	SFX_HANDLE jetSound;

	DWORD transitionTime;
	DWORD newAnimTime;
	Point3F jumpSurfaceNormal;
	float jumpSurfaceLastContact;
	float detectMinSize;
	float detectHazeFactor;
	DWORD m_lastJetTime;
	float gunPullIn;
	bool blownUp;
	int lastContactCount;
	int updateSkip;
	int updateDebt;
	float viewPitch;
	float bounce;
	float traction;
	bool inWorld;
	bool pickUpNewAnimation;
	GameBase* mount;
	bool aiControlled;

	float old_fov;
	float cos_fov;
	float tan_fov;

	bool jetting;

	FearRenderImage flameImage;

	TSShapeInstance::Thread* flameThread;
	TSShapeInstance::Thread* myThread;
	TSShapeInstance::Thread* damageThread;
	TSShape::Transition playerTransition;

	int looksSequence;
	int crouchLooksSequence;

	int animIndex[NUM_ANIMS];
	bool pickNewAnimation;

	int serverAnimation;

	SimTime dieTime;
	bool dead;
	bool crouching;
	bool pdaing;
	bool falling;
	DWORD interpDoneTime;
	bool hasFocus;
	float damageFlash;
	int surfaceType;
	float supressionDist;
	int mountPoint;
	int eyeNode;
	int chaseNode;



	Planet::LensFlare* m_pLensFlare;

	virtual bool getMountTransform(MountPoint mountPoint, TMat3F* mat);

	virtual void disableSupressionField();

	virtual void setBoundingBox();
	virtual int getAnimation();

	virtual void setAnimation(int anim);
	virtual int pickAnimation();
	virtual void updateAnimation(SimTime t);

	virtual bool onSimLightQuery(SimLightQuery* query);
	virtual bool onSimCollisionImageQuery(SimCollisionImageQuery* query);

	virtual bool isFirstPersonView();



	virtual void setPDA(bool tf);
	virtual void updateSelected(int index);
	virtual bool detectItem(GameBase* obj);
	virtual void getDamageLocation(const Point3F& in_rPos, const char*& out_rpVert, const char*& out_rpQuad);
public:
	static ItemImageData* getItemImageData(int imageId);

	void setImageState(int imageSlot, ItemImageEntry::State state);

protected:
	void onRemove() override;
	bool onAdd() override;
	bool initResources(GameBaseData* in_data) override;
	void setDamageLevel(float level) override;
	void getThrowVector(Point3F* pos, Point3F* vec) override;
	float coverage(Point3F eye) override;
	bool onSimObjectTransformEvent(const SimObjectTransformEvent* event);
	bool onSimRenderQueryImage(SimRenderQueryImage* query);
	bool processEvent(const SimEvent* event) override;
	void onCollisionNotify(GameBase* object) override;
	bool processQuery(SimQuery* query) override;
	bool cameraZoomAndCrosshairsEnabled() override;
	void getCameraTransform(float camDist, TMat3F* transform) override;


	void onDeleteNotify(SimObject* object) override;
	int getDatGroup() override;
	const TMat3F& getLOSTransform() override;
	void applyDamage(int type, float value, const Point3F pos, const Point3F& vec, const Point3F& mom, int objectId) override;

public:
	static float prefShapeDetail;
	static float prefPlayerShadowSize;
	static bool prefFreeLook;

	Player();
	virtual ~Player();

	PlayerData* data;
	virtual Point3F getLeadCenter();
	virtual void setInitInfo(const char* in_datFileName, Point3F pos, Point3F rot);

	virtual int getItemCount(int type);
	virtual int incItemCount(int type, int count = 1);
	virtual int decItemCount(int type, int count = 1);
	virtual int setItemCount(int type, int count);

	bool getWeaponAmmoType(ProjectileDataType& out_rPrimary, ProjectileDataType& out_rSecondary) override;

	virtual void serverPlayAnim(int anim);

	virtual void setMountObject(GameBase* object, int in_mountPoint);

	virtual void serverWave(int anim);

	int possibleJetForces(Point3F forces[4], const Point3F * unitLateralDir);
	const Point3F& getLeadVelocity() override;
	bool getVisibleToTeam(int team) override;
	virtual bool isAIControlled() const
	{
		return this->aiControlled;
	}
	virtual int getMountedItem(int imageSlot);
	virtual void setAIControlled(const bool value)
	{
		this->aiControlled = value;
	}

	virtual bool isCrouching() const
	{
		return this->crouching;
	}

	virtual bool isJetting() const
	{
		return this->jetting;
	}

	virtual bool isDead() const
	{
		return this->dead;
	}

	virtual bool isExposed() const
	{
		// TODO:
		return true;
	}

	const ItemImageEntry& getItemImageEntry(Int32 imageSlot) const
	{
		return itemImageList[imageSlot];
	}

	virtual GameBase* getMountObject() const override
	{
		return mount;
	}

	virtual int getLastContactCount() const
	{
		return this->lastContactCount;
	}

	virtual DWORD getLastJetTime() const
	{
		return this->m_lastJetTime;
	}

	virtual float getSupressionField() const
	{
		return this->supressionDist;
	}

	virtual void setSupressionField(float distance);

	const TMat3F& getEyeTransform() override;

	// TODO: Parameter order?
	virtual void setDetectParams(const float minSize, const float hazeFactor)
	{
		this->detectMinSize = minSize;
		this->detectHazeFactor = hazeFactor;
	}

	virtual void setDamageFlash(float df);

	virtual void kill();

	virtual float getViewPitch() const
	{
		return this->viewPitch;
	}

	virtual void setViewPitch(const float value)
	{
		this->viewPitch = value;
	}

	void serverUpdateMove(PlayerMove* moves, int moveCount);


	virtual void resetItemCounts();
	virtual bool useItem(int type);
	virtual bool dropItem(int type);
	virtual bool deployItem(int type);
	virtual int getItemClassCount(const char* itemClass);
	virtual bool mountItem(int type, int imageSlot, int team);
	virtual bool unmountItem(int imageSlot);

	virtual int getNextMountedItem(int imageSlot);

	virtual bool isImageTriggerDown(int imageSlot);
	virtual void setImageTriggerDown(int imageSlot);
	virtual void setImageTriggerUp(int imageSlot);
};
