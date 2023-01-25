#pragma once

#include "Item.h"

class Mine : public Item
{
	typedef Item Parent;

	DECLARE_PERSISTENT(Mine);

protected:
	enum
	{
		MineRotMask = LastMaskBit,
		LastMaskBit = MineRotMask << 1
	};

public:
	struct MineData : ItemData
	{
	private:
		typedef ItemData Parent;

	public:

		MineData();
		void pack(BitStream* stream);
		void unpack(BitStream* stream);
		double explosionRadius;
		double damageValue;
		int damageType;
		float kickBackStrength;
	};

	bool deleteOnDestroy;
	Vector3F groundNormal;
	bool conformed;
	Mine();
	virtual ~Mine();
	bool processArguments(int argc, const char** argv);
	bool initResources(GameBase::GameBaseData* data);
	int getDatGroup();
	bool processCollision(SimMovementInfo* info);
	void onDamageStateChange(DamageState oldState);
	void onCollisionNotify(GameBase* object);
	void sinkIn(float interval);
	void serverProcess(DWORD ct);
	void clientProcess(DWORD ct);
	DWORD packUpdate(Net::GhostManager* gm, DWORD mask, BitStream* stream);
	void unpackUpdate(Net::GhostManager* gm, BitStream* stream);
};
