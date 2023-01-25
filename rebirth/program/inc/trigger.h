#pragma once

#include "GameBase.h"
#include "ShapeBase.h"
#include "boxRender.h"

class Trigger : public GameBase
{
	// TODO: Guess GameBase
	typedef GameBase Parent;

	DECLARE_PERSISTENT(Trigger);

public:
	struct TriggerData : public GameBaseData
	{
	private:
		typedef GameBaseData Parent;

	public:
		float rate;

		TriggerData();
	};

public: //private:
	// TODO: values
	enum
	{
		PositionMask = BIT(24),
		SizedMask = BIT(25)
	};

	struct Pair
	{
		GameBase* object;
		SimTime expire;
		SimTime contact;
	};

	typedef Vector<Pair> TriggerList;
	TriggerList triggerList;

	bool active;
	bool isSphere;

	Point3F rotation;
	bool boundingBoxRotate;

	BoxRenderImage image;

	SimCollisionSphereImage sphereCollisionImage;
	SimCollisionBoxImage boxCollisionImage;

	virtual void syncBoxes();
	virtual bool callScript();
	virtual void onEnter(GameBase* obj);
	virtual void onContact(GameBase* obj);
	virtual void onLeave(GameBase* obj);
	virtual void onActivate();
	virtual void onDeactivate();

	virtual bool onSimObjectTransformQuery(SimObjectTransformQuery* query);
	virtual bool onSimCollisionImageQuery(SimCollisionImageQuery* query);
	virtual bool onSimRenderQueryImage(SimRenderQueryImage* query);
	virtual bool onSimImageTransformQuery(SimImageTransformQuery* query);
	virtual bool onSimObjectTransformEvent(const SimObjectTransformEvent* event);
	virtual bool onSimMovementCollisionEvent(const SimMovementCollisionEvent* event);
	virtual bool onSimTimerEvent(const SimTimerEvent* event);
	virtual bool onSimEditEvent(const SimEditEvent* event);

protected:

	bool isActive() override;
	bool setActive(bool tf) override;
	bool onAdd() override;
	void onRemove() override;
	void onDeleteNotify(SimObject* object) override;
	bool processQuery(SimQuery* query) override;
	bool processEvent(const SimEvent* event) override;
	void inspectWrite(Inspect* inspect) override;
	void inspectRead(Inspect* inspect) override;
	int getDatGroup() override;
	DWORD packUpdate(Net::GhostManager*, DWORD dwMask, BitStream* stream) override;
	void unpackUpdate(Net::GhostManager*, BitStream* stream) override;
	Error write(StreamIO& sio, int iVersion, int iUser) override;
	Error read(StreamIO& sio, int iVersion, int iUser) override;

public:
	Trigger();
	virtual ~Trigger();

	static void initPersistFields();
};
