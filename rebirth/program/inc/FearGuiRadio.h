#pragma once

#include "FearGuiUnivButton.h"

namespace FearGui
{

class FearGuiRadio : public FGUniversalButton
{
	typedef FGUniversalButton Parent;

protected:
	
	Resource<GFXBitmap> mOnBitmap;
	Resource<GFXBitmap> mOffBitmap;

	bool set;
	
public:
	bool becomeFirstResponder();
	bool onAdd();
	void onAction();
	bool onSimActionEvent(const SimActionEvent* event);
	bool processEvent(const SimEvent* event);
	DWORD onMessage(SimObject* sender, DWORD msg);
	void onRender(GFXSurface* sfc, Point2I offset, const Box2I&);
	void inspectWrite(Inspect* insp);
	void inspectRead(Inspect* insp);
	Persistent::Base::Error write(StreamIO& sio, int version, int user);
	Persistent::Base::Error read(StreamIO& sio, int version, int user);

	DECLARE_PERSISTENT(FearGuiRadio);
};

}
