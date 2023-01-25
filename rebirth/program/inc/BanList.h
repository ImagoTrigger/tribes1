#pragma once

#include <ctime>
#include "tVector.h"

class BanList
{
	struct BanInfo
	{
		//	TODO: Array length (256) is guess.
		char transportAddress[256];
		time_t bannedUntil;
	};

	Vector<BanInfo> list;

	static bool isTAEq(const char* bannedTA, const char* TA);
		
public:
	virtual void addBan(const char *TA, time_t banTime);
	virtual void addBanRelative(const char* TA, int numSeconds);
	virtual void removeBan(const char* TA);
	virtual void exportToFile(const char* fileName);	
	virtual bool isBanned(const char* TA);
};

extern BanList gBanList;
