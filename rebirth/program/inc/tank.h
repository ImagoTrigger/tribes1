#pragma once

#include "vehicle.h"

class Tank : public Vehicle
{
	typedef Vehicle Parent;

	DECLARE_PERSISTENT(Tank);

public:

	struct TankData : public VehicleData
	{
		float maxGrade;
		void pack(BitStream* stream) override;
		void unpack(BitStream* stream) override;
	};

public: //private:

	TSShapeInstance::Thread* track1Thread;
	TSShapeInstance::Thread* gunThread;

	TankData* data;

	float pitch;

	void groundMechanics(float adjust);
	void airMechanics(float adjust);
	float getSuspensionHeight(Point3F pos);
	void setDesiredRot(float adjust);

protected:
	bool initResources(GameBaseData* in_data) override;
	void clientProcess(DWORD curTime) override;
	void serverProcess(DWORD curTime) override;
	bool updateMove(PlayerMove* move, float interval) override;
	Error read(StreamIO& sio, int, int) override;
	Error write(StreamIO& sio, int, int) override;
	int getDatGroup() override;

public:
	Tank();
};
