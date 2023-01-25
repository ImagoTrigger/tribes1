#pragma once

#include "fearGuiHudCtrl.h"
#include "simGuiActiveCtrl.h"

namespace FearGui
{
	class FGMenuItem : public SimGui::SimpleText
	{
		typedef SimGui::SimpleText Parent;

		bool mbSet;
		bool mbExpanded;

		SimTag mPageTag;

		Resource<GFXFont> hFontShadow;
		Resource<GFXFont> hFontHeader;

		Resource<GFXBitmap> mClosedDF;
		Resource<GFXBitmap> mClosedON;
		Resource<GFXBitmap> mExpandedDF;
		Resource<GFXBitmap> mExpandedON;

	public:
		FGMenuItem();
		bool onAdd();
		Int32 getMouseCursorTag();
		void calculateExtent();
		void onWake();
		void setState(bool turnOn);
		void setExpanded(bool value);
		DWORD onMessage(SimObject* sender, DWORD msg);
		void onAction();
		void drawText(GFXSurface* sfc, Point2I* offset, Point2I* rect);
		void onRender(GFXSurface* sfc, Point2I offset, const Box2I& updateRect);
		void inspectWrite(Inspect* insp);
		void inspectRead(Inspect* insp);
		Error write(StreamIO& sio, int a, int b);
		Error read(StreamIO& sio, int a, int b);

		bool isSet()
		{
			return mbSet;
		}

		DECLARE_PERSISTENT(FGMenuItem);
	};

	class FGMenuCtrl : public SimGui::ActiveCtrl
	{
		typedef ActiveCtrl Parent;
		
	public:
		bool onAdd();
		void onWake();
		void disableAll();
		void onPreRender();
		void onRender(GFXSurface* sfc, Point2I offset, const Box2I& updateRect);
		
		DECLARE_PERSISTENT(FGMenuCtrl);
	};
}
