#pragma once

#include "simBase.h"

class TeamGroup : public SimGroup
{
	typedef SimGroup Parent;

	DECLARE_PERSISTENT(TeamGroup);

	int teamId;

public:

	TeamGroup();
	virtual ~TeamGroup(){}
	bool onAdd() override;

	virtual int getTeam() const
	{
		return this->teamId;
	}
};
