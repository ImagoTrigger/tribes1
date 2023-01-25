#pragma once

#include "vehicle.h"

class Flier : public Vehicle
{
	typedef Vehicle Parent;

	DECLARE_PERSISTENT(Flier);

public:
	struct FlierData : VehicleData
	{
	private:
		typedef VehicleData Parent;
	public:
		float maxBank;
		float maxPitch;
		float lift;
		float maxAlt;
		float maxVertical;
		float accel;
		float groundDamageScale;

		void pack(BitStream* stream) override;
		void unpack(BitStream* stream) override;
	};

	static bool flipYAxis;

	FlierData* data;
	bool landed;
	float lateralThrust;
	float minAlt;
	float maxAlt;
	bool braking;
	bool thrusting;
	float bounce;

	int thrustSequence;
	int idleSequence;

	TSShapeInstance::Thread* tiltThread;
	TSShapeInstance::Thread* flameThread;

	Flier();
	virtual void setMaxAlt();
	virtual void setMinAlt();
	virtual const Point3F& getLeadVelocity();
	virtual void dynamics(float adjust);

protected:
	bool initResources(GameBaseData* in_data) override;
	void clientProcess(DWORD curTime) override;
	void serverProcess(DWORD curTime) override;
	bool updateMove(PlayerMove* move, float interval) override;
	bool processCollision(SimMovementInfo* info) override;
	void readPacketData(BitStream* bstream) override;
	void writePacketData(BitStream* bstream) override;
	DWORD packUpdate(Net::GhostManager* g, DWORD mask, BitStream* stream) override;
	void unpackUpdate(Net::GhostManager* gm, BitStream* stream) override;
	Error read(StreamIO& sio, int, int) override;
	Error write(StreamIO& sio, int, int) override;
	int getDatGroup() override;
	bool processQuery(SimQuery* query) override;
	bool onSimRenderQueryImage(SimRenderQueryImage* query);
};
