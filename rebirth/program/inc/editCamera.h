#pragma once

#include "FlyingCamera.h"

class EditCamera : public FlyingCamera
{
	// TODO: Parent?
	typedef FlyingCamera Parent;

	// TODO: Values
	enum
	{
		Mod1 = BIT(0),
		Mod2 = BIT(1),
		Mod3 = BIT(2),
	};
	
	int lastUpdate;

	MoveLinear movement;
	MoveLinear rotation;
	
	Resource<SimActionMap> actionMap;

public:
	DECLARE_PERSISTENT(EditCamera);
	
	EditCamera();
	virtual ~EditCamera();
	void update(SimTime dt);
	const Point3F& getPos();
	void setPos(Point3F pos);
	void setActionMap(const char* file);
	bool processArguments(int argc, const char** argv);
	bool onAdd();
	void resetSystemKeys();
	bool processEvent(const SimEvent* event);
	bool processQuery(SimQuery* query);
	float getFarPlane();
	void onDeleteNotify(SimObject* io_pDelete);
};
