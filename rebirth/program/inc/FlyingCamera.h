#pragma once

#include "GameBase.h"
#include "InputHandler.h"

class FlyingCamera : public GameBase
{
	typedef GameBase Parent;

	DECLARE_PERSISTENT(FlyingCamera);

	
protected:

	bool fActivated;
	// TODO: Length
	char szGUIFileName[256];
	// TODO: Length
	char szGUIObjName[256];
	// TODO: Length
	char szSAEName[256];
	SimObject* objFollow;
	Point3F throttle;
	Point3F rotation;
	Point3F position;
	SimCollisionSphereImage collisionImage;
	Point3F maxLinearSpeed;
	Point3F maxAngularSpeed;
	Net::PacketStream* watchPacketStream;

	struct
	{
		struct
		{
			InputHandler x;
			InputHandler y;
			InputHandler z;
		} linear;

		struct
		{
			InputHandler x;
			InputHandler y;
			InputHandler z;
		} angular;
	}input;

	int iCurrentObserved;
	float rDistance;

	bool onAdd() override;
	bool processArguments(int argc, const char** argv) override;
	bool processEvent(const SimEvent* event) override;
	bool processQuery(SimQuery* query) override;
	void onDeleteNotify(SimObject* io_pDelete) override;

public:
	FlyingCamera();
	virtual ~FlyingCamera();
	void activate(bool fFreeFly);
	bool onSimFrameEndNotifyEvent(const SimFrameEndNotifyEvent*);
	bool onSimObjectTransformEvent(const SimObjectTransformEvent* event);
	bool handleAction(int iAction, float rValue, int iDevice);
	void pushActionMap();
	void popActionMap();
	bool onSimGainFocusEvent(const SimGainFocusEvent*);
	bool onSimLoseFocusEvent(const SimLoseFocusEvent*);
	bool onSimCameraQuery(SimCameraQuery* query);
	bool onSimCollisionImageQuery(SimCollisionImageQuery* query);
	bool onSimObjectTransformQuery(SimObjectTransformQuery* query);
	bool onSimImageTransformQuery(SimImageTransformQuery* query);
	bool attachToObject(SimObject* obj);
	void reset();
	void setFreeFlyMode();
	void nextObservable(bool fForward);
	void findLOSPosition(TMat3F& tmat, const Point3F& objPos);
	void updateGUIInfo();
	void attachToGUI();
	float getFarPlane();
};
