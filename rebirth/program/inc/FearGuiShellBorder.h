#pragma once

#include "simGuiMatrixCtrl.h"
#include "simGuiBitmapCtrl.h"
#include "FearGuiArrayCtrl.h"

namespace FearGui
{
	class FGShellBorder : public SimGui::Control
	{
		typedef SimGui::Control Parent;

		DECLARE_PERSISTENT(FGShellBorder);

		// TODO: values
		enum
		{
			BMP_BottomLeft,
			BMP_BottomLeft2,
			BMP_BottomRight = 3,
			BMP_BottomRight2,
			BMP_StretchBottom,
			BMP_StretchLeft,
			BMP_StretchRight,
			BMP_StretchTop,
			BMP_TopEdge,
			BMP_TopEdge2,
			BMP_TopLeft,
			BMP_TopLeft2,
			BMP_TopRight,
			BMP_TopRight2,
			BMP_Count = BMP_TopRight2
		};

		SimGui::BitmapCtrl bkgndCtrl;

		const char* bitmapName;
		Resource<GFXBitmap> bkgndBitmap;

		Resource<GFXBitmapArray> bma;

		SimTag pbaTag;

	public:
		void onPreRender();
		void onRender(GFXSurface* sfc, Point2I offset, const Box2I& updateRect);
		void inspectRead(Inspect* insp);
		void inspectWrite(Inspect* insp);
		bool onAdd();
		Persistent::Base::Error read(StreamIO& sio, int version, int user);
		Persistent::Base::Error write(StreamIO& sio, int version, int user);
		FGShellBorder();
		void loadBitmapArray();
	};

	class MMShellBorder : public FGShellBorder
	{
		typedef FGShellBorder Parent;

		DECLARE_PERSISTENT(MMShellBorder);
	};
}
