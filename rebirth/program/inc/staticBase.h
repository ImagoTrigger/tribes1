#pragma once

#include "ShapeBase.h"
#include "SimCollision.h"
#include "simCollisionImages.h"

class StaticBase : public ShapeBase
{
	typedef ShapeBase Parent;

	static const size_t DamageLevelBits = 6;

public:
	struct StaticBaseData : public ShapeBaseData
	{
	private:
		typedef ShapeBaseData Parent;

	public:
		int sfxAmbient;
		struct Damage
		{
			float disabled;
			float destroyed;
		} damageLevel;
		float maxDamage;
		bool isTranslucent;
		float outerRadius;
		bool disableCollision;

		StaticBaseData();
		void pack(BitStream* stream) override;
		void unpack(BitStream* stream) override;
	};

protected:

	bool deleteOnDestroy;

	// TODO: Order also values, flags?
	enum DamageState
	{
		None,
		Enabled,
		Disabled,
		Destroyed
	};

	virtual DamageState getState() { return None; }

	virtual SimTime getAnimateDelta(DWORD curTime)
	{
		return ((curTime - cg.lastTime) / 1000.0);
	}

	DamageState state;


public: //private:



	bool m_isTarget;

	StaticBaseData* data;

	TSShapeInstance::Thread* ambientThread;
	TSShapeInstance::Thread* damageThread;

	SFX_HANDLE ambientSound;


	bool active;

	int getDamageSkinLevel(int detailLevel) override;
	const char* getDamageState() override;

	// Overridden to update damage state.
 	void setDamageLevel(float level) override;

	// Overridden to notify SimNetObject that the position and rotation has changed.
	bool onSimObjectTransformEvent(const SimObjectTransformEvent* event);

protected:

	//ShapeCollisionImage collisionImage;


	bool processArguments(int argc, const char** argv) override;
	bool initResources(GameBaseData* dat) override;
	bool onAdd() override;
	void onRemove() override;
	void scriptOnAdd() override;
	bool isActive() override;
	bool setActive(bool a) override;
	bool getCommandStatus(CommandStatus* status) override;
	bool processEvent(const SimEvent* event) override;
	void onPowerStateChange(GameBase* generator) override;
	void onCollisionNotify(GameBase* object) override;
	void serverProcess(DWORD) override;
	void clientProcess(DWORD curTime) override;
	bool processQuery(SimQuery* query) override;
	bool onSimRenderQueryImage(SimRenderQueryImage* query);
	DWORD packUpdate(Net::GhostManager* gm, DWORD mask, BitStream* stream) override;
	void unpackUpdate(Net::GhostManager* gm, BitStream* stream) override;
	Error read(StreamIO& sio, int, int) override;
	Error write(StreamIO& sio, int, int) override;

	// Overridden to update ambient noise loop location.
	void setPos(const Point3F& pos) override;

public:
	static float prefShapeDetail;

	StaticBase();
	virtual ~StaticBase();

	//virtual SimTime getAnimateDelta(DWORD curTime) const
	//{
	//	throw std::exception("NYI");
	//}

	virtual void initCollisionInfo();
	virtual void updateState();
	
	virtual void setState(DamageState newState, bool script = true);

	virtual void onActivate();
	virtual void onDeactivate();
	virtual void startAmbientSound();
	virtual void stopAmbientSound();

	virtual void onDamageStateChange(DamageState oldState);

	virtual void setDetailScale();
	virtual bool onSimCollisionImageQuery(SimCollisionImageQuery* query);
	static void initPersistFields();
	virtual bool setIsTarget(const bool in_isTarget);
	virtual bool getTarget(Point3F* out_pTarget, int* out_pTeam);

	virtual DamageState getState() const
	{
		return this->state;
	}

	virtual bool isTarget() const
	{
		return this->m_isTarget;
	}

	virtual float getDisableLevel() const
	{
		return this->data->damageLevel.disabled;
	}
};

class StaticShape : public StaticBase
{
	typedef StaticBase Parent;

	DECLARE_PERSISTENT(StaticShape);

public:
	struct StaticShapeData : public StaticBaseData
	{
	};

protected:

	int getDatGroup() override;
	DWORD packUpdate(Net::GhostManager* gm, DWORD mask, BitStream* stream) override;
	void unpackUpdate(Net::GhostManager* gm, BitStream* stream) override;
	Error read(StreamIO & sio, int ver, int user) override;
	Error write(StreamIO& sio, int ver, int user) override;
	bool processQuery(SimQuery* query) override;

public:
	StaticShape();
	virtual ~StaticShape();
};
