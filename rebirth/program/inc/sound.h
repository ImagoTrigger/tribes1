#pragma once

#include "GameBase.h"
#include "SoundFX.h"

struct SoundEvent : public SimEvent
{
	typedef SimEvent Parent;

	DECLARE_PERSISTENT(SoundEvent);

	int id;
	int ghostIndex;
	int channel;
	SoundEvent();
	void pack(SimManager *manager, Net::PacketStream *ps, BitStream *bs) override;
	void unpack(SimManager *manager, Net::PacketStream *ps, BitStream *bs) override;
};

struct SoundProfileData : public GameBase::GameBaseData
{
	Sfx::Profile profile;
	float dist;

	SoundProfileData();
	bool preload(ResourceManager *, bool, char errorBuffer[256]);
	void pack(BitStream* bstream);
	void unpack(BitStream* bstream);
};

struct SoundData : public GameBase::GameBaseData
{
	StringTableEntry wavFileName;
	int priority;
	int profileIndex;
	SoundProfileData* pro;
	
	SoundData();

	bool preload(ResourceManager * rm, bool server, char errorBuffer[256]);

	void pack(BitStream* bstream);
	void unpack(BitStream* bstream);
};
