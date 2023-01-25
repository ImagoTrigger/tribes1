#pragma once
#include "MoveableBase.h"

class Elevator : public MoveableBase
{
	typedef MoveableBase Parent;

	DECLARE_PERSISTENT(Elevator);

	Elevator();

protected:
	int getDatGroup() override;
	Error read(StreamIO& sio, int iVer, int iUsr) override;
	Error write(StreamIO& sio, int iVer, int iUsr) override;

public:

	virtual ~Elevator();
};
