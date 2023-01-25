#pragma once

#include "GameBase.h"

class DataBlockEvent : public SimEvent
{
	friend class DataBlockManager;

	DECLARE_PERSISTENT(DataBlockEvent);

	int group;
	int gsize;
	int block;
	GameBase::GameBaseData* data;

protected:
	void pack(SimManager* manager, Net::PacketStream* ps, BitStream* bstream) override;
	void unpack(SimManager* manager, Net::PacketStream* ps, BitStream* bstream) override;

public:
	DataBlockEvent();
};

class DataBlockManager : public SimNetObject
{
	typedef SimNetObject Parent;

public:
	enum
	{
		SoundProfileDataType,
		SoundDataType,
		DamageSkinDataType,
		PlayerDataType,
		StaticShapeDataType,
		ItemDataType,
		ItemImageDataType,
		MoveableDataType,
		SensorDataType,
		VehicleDataType,
		FlierDataType,
		TankDataType,
		HoverDataType,
		ProjectileDataType,
		BulletDataType,
		GrenadeDataType,
		RocketDataType,
		LaserDataType,
		InteriorShapeDataType,
		TurretDataType,
		ExplosionDataType,
		MarkerDataType,
		DebrisDataType,
		MineDataType,
		TargetLaserDataType,
		SeekingMissileDataType,
		TriggerDataType,
		CarDataType,
		LightningDataType,
		RepairEffectDataType,
		IRCChannelType,
		NumDataTypes
	};

public: //private:

	// TODO: Get real size;
	static const size_t HashTableSize = 1024;

	// TODO: Get real mask.
	static const size_t HashTableMask = 1023;

	bool isServer;
	int curBlock;
	int curGroup;
	int numBlocksRemaining;
	void* lastDataBlock;
	const char* lastDataBlockName;

	GameBase::GameBaseData* hashTable[HashTableSize];

	VectorPtr<GameBase::GameBaseData*> dataBlocks[NumDataTypes];

protected:
	bool processEvent(const SimEvent* event) override;

public:
	explicit DataBlockManager(bool in_isServer);
	virtual ~DataBlockManager();

	virtual int getDataGroupBitSize(int group);
	virtual void reset();
	virtual void sendDataToClient(int clientManagerId);
	virtual GameBase::GameBaseData* createDataBlock(int blockType);
	virtual bool serverPreload();

	virtual GameBase::GameBaseData* lookupDataBlock(int blockId, int groupId);
	virtual const char* lookupBlockName(int blockId, int groupId);
	virtual GameBase::GameBaseData* lookupDataBlock(const char* name, int groupId, int& blockId);
	virtual GameBase::GameBaseData* lookupDataBlock(const char* name);
	virtual void createBlock(const char* name, int type, void* classPtr);

	virtual void writeBlockId(BitStream* const stream, int blockType, int value)
	{
		const Int32 bitCount = 8;//this->getDataGroupBitSize(blockType);
		return stream->writeInt(value + 1, bitCount);
	}

	virtual int readBlockId(BitStream* const stream, int blockType)
	{
		const Int32 bitCount = 8;//this->getDataGroupBitSize(blockType);
		return stream->readInt(bitCount) - 1;
	}

	virtual int getDataGroupSize(const int dataGroup)
	{
		return dataBlocks[dataGroup].size();
		//return getDataGroupBitSize(dataGroup) << 3;
	}
};
