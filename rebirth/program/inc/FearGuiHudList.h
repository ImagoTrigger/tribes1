#pragma once

#include "FearGuiHudArrayCtrl.h"

namespace FearGui
{
	class HudListCtrl : public FGHudArrayCtrl
	{
		typedef FGHudArrayCtrl Parent;
		typedef FGArrayCtrl Grandparent;

		Resource<GFXFont> hFontShadow;
		
		Resource<GFXFont> lrFont;
		Resource<GFXFont> lrFontShadow;
		
		Resource<GFXBitmap> mHudOnBmp;
		Resource<GFXBitmap> mHudOffBmp;

		Resource<GFXBitmap> lrHudOnBmp;
		Resource<GFXBitmap> lrHudOffBmp;

		bool mbLowRes;
				
	public:
		DECLARE_PERSISTENT(HudListCtrl);

		
		Int32 getMouseCursorTag(void);
		void onMouseDown(const SimGui::Event& event);
		bool onAdd();
		void onWake();
		void onPreRender();
		void onRenderCell(GFXSurface* sfc, Point2I offset, Point2I cell, bool, bool);
		void onRender(GFXSurface* sfc, Point2I offset, const Box2I& updateRect);
	};
}
