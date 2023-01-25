#pragma once

#include "FearGuiRadio.h"

namespace FearGui
{

class FGCommandRadio : public FearGuiRadio
{
	typedef FearGuiRadio Parent;
	typedef FGUniversalButton GrandParent;

	SimTag mCmdTag;
	
	SimTag bmpOnTag;
	SimTag bmpOffTag;

	SimTag loResBmpOnTag;
	SimTag loResBmpOffTag;

	bool mLowRes;

	Point2I hiResPosition;
	Point2I hiResExtent;
	Point2I loResPosition;
	Point2I loResExtent;

	Resource<GFXBitmap> mLoResOnBitmap;
	Resource<GFXBitmap> mLoResOffBitmap;
	
public:
	FGCommandRadio();
	bool onAdd();
	void onWake();
	void setLowRes(bool lores);
	DWORD onMessage(SimObject* sender, DWORD msg);
	void onAction();
	void onRender(GFXSurface* sfc, Point2I offset, const Box2I&);
	void setBitmaps();
	void inspectWrite(Inspect* insp);
	void inspectRead(Inspect* insp);
	Persistent::Base::Error write(StreamIO& sio, int version, int user);
	Persistent::Base::Error read(StreamIO& sio, int version, int user);

	DECLARE_PERSISTENT(FGCommandRadio);
};

}