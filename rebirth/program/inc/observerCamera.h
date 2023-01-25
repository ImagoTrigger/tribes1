#pragma once

#include "FearPlayerPSC.h"
#include "moveable.h"

class ObserverCamera : public GameBase
{
	// TODO: Guess GameBase
	typedef GameBase Parent;

	DECLARE_PERSISTENT(ObserverCamera);



	EulerF rotation;
	Point3F position;
	bool inWorld;
	int clientId;
	float curOrbitDist;
	float minOrbitDist;
	float maxOrbitDist;

	// TODO: Value order
	enum
	{
		StationaryMode,
		FreeRotateMode,
		FlyMode,
		OrbitObjectMode,
		OrbitPointMode
	};
	int mode;

	GameBase* orbitObject;
	GameBase* damageObject;

	PlayerMove pmLast;


	void update(DWORD, DWORD tickEnd, PlayerMove* pm);

protected:
	bool onAdd() override;
	float getDamageLevel() override;
	float getEnergyLevel() override;
	float getDamageFlash() override;
	bool getCommandStatus(CommandStatus* status) override;
	void setPlayerControl(bool ctrl) override;
	void onDeleteNotify(SimObject* object) override;

	void readPacketData(BitStream* bstream) override;
	void writePacketData(BitStream* bstream) override;
	void serverUpdateMove(PlayerMove* rgpm, int iCount) override;
	void buildScopeAndCameraInfo(Net::GhostManager* gm, CameraInfo* camInfo) override;
	void clientProcess(DWORD curTime) override;
	const TMat3F& getEyeTransform() override;

public:
	// TODO: Real default
	ObserverCamera(int in_clientId = 2048);
	virtual ~ObserverCamera();

	bool isEyesView(GameBase* gb);

	//void setFlyMode(bool canMove, bool canRotate, const Point3F& pos, const Point3F& rot);
	void setOrbitMode(GameBase* obj, Point3F& pos, Point3F& rot, float minDist, float maxDist, float curDist);
	void setFlyMode(bool canMove, bool canRotate, Point3F& pos, Point3F& rot);

	void setDamageObject(GameBase* object);

	GameBase* getOrbitObject() const
	{
		return this->orbitObject;
	}

	//void setOrbitMode(GameBase* obj, const Point3F& pos, const  Point3F& rot, float minDist, float maxDist, float curDist);
};
