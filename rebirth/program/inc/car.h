#pragma once

#include "vehicle.h"

class Car : public Vehicle
{
	typedef Vehicle Parent;

	DECLARE_PERSISTENT(Car);

public:
	struct CarData : public VehicleData
	{
	private:
		typedef VehicleData Parent;

	public:
		int wheelCount;
		struct
		{
			bool steerForward;
			bool steerReverse;
			Point3F wheelBase;
		} wheels[6];

		float wheelRadius;
		float wheelRestDist;
		float wheelOneGDist;

		float wheelSideBrakeForce;
		float turnAngle;
		const char* wheelShapeName;


		CarData();
		void pack(BitStream* stream) override;
		void unpack(BitStream* stream) override;
	};

	CarData* data;

	DWORD lpt;
	Vector3F omega;
	Vector3F velocity;
	float forwardDir;
	float sideDir;
	float wheelRot;
	float accel;

	Vector3F wheelNormal[6];
	float wheelDist[6];
	RenderImage wheelRenderImage[6];


	Car();

	void getVelocity(Point3F worldPos, Point3F* vel);
	void update(DWORD start, DWORD end, PlayerMove* move);
	void processWheelSpring(int wheel, Point3F* sigmaF, Point3F* sigmaT);
	void processWheelMove(int wheel, float dt, Point3F* sigmaF, Point3F* sigmaT);
	void rotate(Point3F w);
	void addAcceleration(Point3F r, const Point3F& F, Point3F* sigmaF, Point3F* sigmaT);
	void applyDampenDeltaV(Point3F r, Point3F& dir, float, Point3F*, Point3F*);

protected:
	int getDatGroup() override;
	void clientProcess(DWORD curTime) override;
	bool cameraZoomAndCrosshairsEnabled() override;
	void getCameraTransform(float camDist, TMat3F* transform) override;
	bool onSimRenderQueryImage(SimRenderQueryImage* query);
	bool processQuery(SimQuery* query) override;
	bool initResources(GameBaseData* dat) override;
	DWORD packUpdate(Net::GhostManager* gm, DWORD mask, BitStream* stream) override;
	void unpackUpdate(Net::GhostManager* gm, BitStream* stream) override;

};
