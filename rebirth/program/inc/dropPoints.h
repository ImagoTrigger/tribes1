#pragma once

#include "SimBase.h"
#include "FearDcl.h"

struct DropPointQuery : public SimQuery
{
	const char* dropPointName;
	TMat3F tmat;

	DropPointQuery()
	{
		type = DropPointQueryType;
	}
};

class DropPointGroup : public SimGroup
{
	typedef SimGroup Parent;

	DECLARE_PERSISTENT(DropPointGroup);

	int currentIndex;
	bool random;

public:
	DropPointGroup();
	virtual ~DropPointGroup();
	bool onDropPointQuery(DropPointQuery* query);
	bool processQuery(SimQuery* query);
	void inspectWrite(Inspect* s);
	void inspectRead(Inspect* s);
	Persistent::Base::Error read(StreamIO& s, int version, int user);
	Persistent::Base::Error write(StreamIO& s, int version, int user);
};
