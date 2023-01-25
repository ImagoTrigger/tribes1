#pragma once

#include "simGuiCtrl.h"

namespace FearGui
{
	class FGCommandView : public SimGui::Control
	{
		typedef Control Parent;

		enum
		{
			BMP_TopLeft,
			BMP_TopLeft2,
			BMP_BottomLeft,
			BMP_BottomLeft2,
			BMP_BottomEdge,
			BMP_BottomRight2,
			BMP_BottomRight,
			BMP_RightEdge,
			BMP_TopRight,
			BMP_TopEdge2,
			BMP_TopEdge1,
			BMP_StretchTop,
			BMP_StretchLeft,
			BMP_StretchBottom,
			BMP_StretchRight,
			BMP_Count
		};

		float alphaBlend;
		ColorF alphaColor;
		float prevAlphaBlend;

		bool mLowRes;
		Resource<GFXBitmapArray> bma;
		SimTag pbaTag;
		SimTag lr_pbaTag;
		
	public:
		void onPreRender();
		void onRender(GFXSurface* sfc, Point2I offset, const Box2I& updateRect);
		void onWake();
		bool onAdd();
		void loadBitmapArray();

		DECLARE_PERSISTENT(FGCommandView);
	};
}
