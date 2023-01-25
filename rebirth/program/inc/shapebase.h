#pragma once

#include "GameBase.h"
#include "ts_shapeinst.h"
#include "SimResource.h"
#include "TSFX.h"
#include "Console.h"
#include "fearGlobals.h"
#include "gdmanag.h"
#include "shapeCollision.h"

class SThread;

class ShapeBase : public GameBase
{
	typedef GameBase Parent;

	DECLARE_PERSISTENT(ShapeBase);

public:
	static const int MaxSequenceIndex = 16;

	// TODO: Verify value is correct.
	static const size_t MaxScriptThreads = 3;

	// TODO: Verify value is correct.
	static const int MaxSoundChannels = 16;

	static const size_t ThreadSequenceBits = 4;

	struct ShapeBaseData : public GameBaseData
	{
	private:
		typedef GameBaseData Parent;

	public:

		const char* fileName;
		const char* shieldShapeName;
		int damageSkinId;
		int sfxShield;
		int shadowDetailMask;
		int explosionId;
		int debrisId;
		float maxEnergy;
		float maxDamage;
		float repairRate;

		struct SequenceSound
		{
			const char* sequence;
			SimObjectId sound;
		} sequenceSound[MaxSequenceIndex];

		Resource<TSShape> shieldShape;
		Resource<TSShape> shape;

		bool isPerspective;

		ShapeBaseData();

		void pack(BitStream* stream) override;
		void unpack(BitStream* stream) override;
		bool preload(ResourceManager* rm, bool server, char errorBuffer[256]) override;
	};

	struct DamageSkinData : public GameBaseData
	{
		typedef GameBaseData Parent;

		static const int BmpCount = 10;

		const char* bmpName[BmpCount];
		Resource<GFXBitmap> bmps[BmpCount];
		int numBmps;

		DamageSkinData();
		void pack(BitStream* stream) override;
		void unpack(BitStream* stream) override;
	};

protected:
	static const DWORD csm_fadeLength;

protected:
	// TODO: Values
	enum
	{
		InfoMask = LastMaskBit,
		PositionMask = LastMaskBit << 1,
		RotationMask = LastMaskBit << 2,
		OrientationMask = LastMaskBit << 3,
		DamageMask = LastMaskBit << 4,
		ShieldMask = LastMaskBit << 5,
		SBFadeMask = LastMaskBit << 6,
		ThreadMask = LastMaskBit << 7,
		ThreadNMask = ThreadMask << MaxScriptThreads,
		LastMaskBit = ThreadNMask << 1
	};

	enum
	{
		//NameMask = Parent::NextFreeMask,
		//DamageMask = Parent::NextFreeMask << 1,
		//NoWarpMask = Parent::NextFreeMask << 2,
		//MountedMask = Parent::NextFreeMask << 3,
		//CloakMask = Parent::NextFreeMask << 4,
		//ShieldMask = Parent::NextFreeMask << 5,
		//InvincibleMask = Parent::NextFreeMask << 6,
		//SkinMask = Parent::NextFreeMask << 7,
		//SoundMaskN = Parent::NextFreeMask << 8,
		//ThreadMaskN = SoundMaskN << MaxSoundThreads,
		//ImageMaskN = ThreadMaskN << MaxScriptThreads,
		//NextFreeMask = ImageMaskN << MaxMountedImages

		// values previously it was assumed
		//	that bits 0-X were reserved, which is why
		//	24 was arbitrarily chosen as a 'guess' of where to begin
		// But SimLight seems to indicate this is not the case.
		// and implementations are free to use masks starting at 0.
		//ShieldMask = BIT(23),
		//DamageMask = BIT(24),
		//InfoMask = BIT(25),
		//ThreadMask = BIT(26),
		//ThreadNMask = BIT(27),
		//PositionMask = BIT(28),
		//RotationMask = BIT(29),
		//OrientationMask = BIT(22),
		//SBFadeMask = BIT(30)

	};

public:
	static bool prefUseCustomSkins;
	static int prefDamageSkinDetail;
	static int prefShadowDetailMask;
	static float prefShadowDetailScale;
	static bool renderBoundingBox;
	static bool renderLightRays;

	class RenderImage : public FearRenderImage
	{
		// TODO: Guess FearRenderImage
		typedef FearRenderImage Parent;

	protected:
		void render(TSRenderContext& rc) override;

	public:
		ShapeBase* pOwner;

		void renderBoundingBox(TSRenderContext& rc) override;
		void updateSunOverride(const bool in_attenuate, const float in_factor, const ColorF& in_color) override;

		void setContainerBox(const Box3F box)
		{
			this->m_containerBox = box;
		}
	};

public:
	ShapeBaseData* data;

	struct SThread
	{
		/// State of the animation thread.
		enum {
			Play, Stop, Pause
		};
		TSShapeInstance::Thread* thread; ///< Pointer to 3space data.
		UInt32 state;        ///< State of the thread


		Int32 sequence;     ///< The animation sequence which is running in this thread.
		SFX_HANDLE sound;        ///< Handle to sound.
		bool atEnd;       ///< Are we at the end of this thread?
		bool forward;
	} scriptThread[MaxScriptThreads];

	bool blowedUpGood;

	TSShapeInstance::Thread* shieldThread;

	Point3F shieldVec;
	float zOffset;

	int m_ticks;


	ColorF m_rollColor;
	float m_rollFactor;

	Resource<TS::MaterialList> materialList;

	SFX_HANDLE soundChannel[MaxSoundChannels];

	// TODO: Are these GameBase?

	float repairReserve;

	float autoRepairRate;

	bool destroyable;

	// End possible GameBase fields

	const char* curSkin;
	int curSkinDamage;

	float movementStepSize;

	virtual const char* getSkinBase();
	virtual void damageBitmap(GFXBitmap* bmp);
	virtual void buildMaterialList();
	virtual int getDamageSkinLevel(int detailLevel);

	virtual void animateRoot();

	virtual void setShieldThread(float p);

	virtual void updateSequence(SThread & st);

	virtual void stopSound(SThread& thread);
	virtual void startSound(SThread& thread);

	virtual const Point3F& getCenter();

	bool onSimObjectTransformQuery(SimObjectTransformQuery* query);
	bool onSimImageTransformQuery(SimImageTransformQuery* query);

	virtual void updateSunRollAv();
	virtual bool getLOSColor(const Point3F& in_rShootPoint, const Point3F& in_rVec, float in_dist, ColorF& out_rColor, float& out_rFactor, SimContainer*& out_rpContainer);


protected:
	bool m_attenuateSun;
	ColorF m_attenuationColor;
	float m_attenuationFactor;

	ShapeCollisionImage collisionImage;
	SimCollisionSphereImage outerCollisionImage;
	RenderImage image;
	FearRenderImage shieldImage;

	virtual void blowUp();
	virtual void unBlowUp();

	Point3F rotation;
	DWORD m_fadeStarted;

	DWORD m_lastSunUpdated;
	float damageLevel;
	float energy;
	float rechargeRate;

	enum
	{
		NotFading,
		FadingOut,
		FadingIn
	} m_fading;

	virtual const Point3F& getAnimTransform();


	bool getCommandStatus(CommandStatus* status) override;

	bool onAdd() override;
	void onRemove() override;

	bool initResources(GameBaseData* dat) override;

	bool processEvent(const SimEvent* event) override;
	bool processQuery(SimQuery* query) override;

	DWORD packUpdate(Net::GhostManager* gm, DWORD mask, BitStream* stream) override;
	void unpackUpdate(Net::GhostManager* gm, BitStream* stream) override;

	void inspectWrite(Inspect* inspector) override;
	void inspectRead(Inspect* inspector) override;
	Error read(StreamIO& sio, int, int) override;
	Error write(StreamIO& sio, int, int) override;

	bool onSimRenderQueryImage(SimRenderQueryImage* query);
	bool onSimObjectTransformEvent(const SimObjectTransformEvent* event);

	virtual bool aimedTransform(TMat3F* eyeMat, Point3F startPoint);
	virtual void setPos(const Point3F& pos);
	virtual void setRot(const Point3F& rot);
	virtual bool getPositionalColor(ColorF& out_rColor, float& out_rSunAttenuation);
	virtual void updateSunOverride(const bool in_overrideSun, const float in_sunAttenuation, const ColorF& in_positionalColor);
	virtual void updateMovement(float slice);

	virtual void updateDamage(SimTime t);
	virtual void updateEnergy(SimTime t);
	virtual void updateShieldThread(SimTime t);
	virtual void updateScriptThreads(SimTime t);

	virtual void clearAnimTransform();

	virtual TS::ShapeInstance::Thread* createThread(int seqNum);

	void setTeam(int teamId) override;

public:
	ShapeBase();
	virtual ~ShapeBase();

	static void initPersistFields();

	virtual void serverBlowUp()
	{
		this->blowUp();
	}
	virtual bool getAimedMuzzleTransform(int slot, TMat3F* mat);
	virtual float coverage(Point3F eye);
	virtual float getRadius();

	virtual const TSShape& getTSShape();

	virtual bool setSequence(int slot, int seq, bool reset = true);
	virtual bool playSequence(int slot);
	virtual bool stopSequence(int slot);
	virtual bool pauseSequence(int slot);
	virtual bool setSequenceDir(int slot, bool forward);

	float getDamageLevel() override
	{
	   float returnVal = (damageLevel / data->maxDamage);
	   if(returnVal > 1)
	      returnVal = 1;
	   if(returnVal < 0)
	      returnVal = 0;
		return returnVal;
	}
	float getEnergyLevel() override;

	virtual const char* getDamageState();
	virtual void setDamageLevel(float level);

	virtual void setShieldVec(Point3F hv, float zoff);

	virtual void startFadeOut();
	virtual void startFadeIn();

	virtual Point3F getPos() const
	{
		return this->lPosition;
	}

	virtual Point3F getRot() const
	{
		return this->rotation;
	}

	// TODO: default false?
	virtual void reSkin(bool force = false);

	virtual void applyDamage(int type, float value, const Point3F pos, const Point3F& vec, const Point3F& mom, int objectId);
	virtual bool repairDamage(float amount);

	virtual GameBase* getMountObject() const
	{
		// TODO:
		//throw std::exception("NYI");
		return nullptr;
	}

	virtual float getEnergy() const
	{
		return this->energy;
	}
	virtual void setEnergy(float ee);

	virtual void setRechargeRate(float rate);
	virtual float getRechargeRate() const
	{
		return this->rechargeRate;
	}

	virtual void setAutoRepairRate(float rate);
	virtual float getAutoRepairRate() const
	{
		return this->autoRepairRate;
	}

	virtual SimObject* findLOSObject(const TMat3F& mat, float range, int mask, Point3F* pos, Point3F* normal);
	virtual const TMat3F& getLOSTransform();
};
