#pragma once

#include "StaticBase.h"

class Sensor : public StaticBase
{
	// TODO: StaticShape Guess? StaticBase?
	typedef StaticBase Parent;

	DECLARE_PERSISTENT(Sensor);

public:

	struct SensorData : public StaticBaseData
	{
	private:
		typedef StaticBaseData Parent;

	public:
		bool fCastLOS;
		int iRange;
		int iDopplerVelocity;
		bool supression;
		bool supressable;
		bool pinger;

		SensorData();

		void pack(BitStream* stream) override;
		void unpack(BitStream* stream) override;
	};

public: //private:

	SensorData* sensorData;
	Box3F sensorBox;


	virtual void buildSensorBox();

	virtual SimObject* checkLOS(Point3F& position);

protected:
	bool onAdd() override;
	void setTeam(int teamId) override;
	void onRemove() override;
	int getDatGroup() override;
	bool initResources(GameBaseData* gbData) override;
	DWORD packUpdate(Net::GhostManager* gm, DWORD dwMask, BitStream* stream) override;
	void unpackUpdate(Net::GhostManager* gm, BitStream* stream) override;
	Error read(StreamIO& sio, int iVer, int iUsr) override;
	Error write(StreamIO& sio, int iVer, int iUsr) override;

public:
	Sensor* prevSensor;
	Sensor* nextSensor;

	Sensor();
	virtual ~Sensor();
	virtual bool detectItem(GameBase* obj);

	virtual bool isSupressionSensor() const
	{
		if(this->sensorData)
		{
			return this->sensorData->supression;
		}
		return false;
	}

	virtual bool isSupressableSensor() const
	{
		if(this->sensorData)
		{
			return this->sensorData->supressable;
		}
		return true;
	}

	virtual bool isPinger() const
	{
		if(this->sensorData)
		{
			return this->sensorData->pinger;
		}
		return true;
	}
};
