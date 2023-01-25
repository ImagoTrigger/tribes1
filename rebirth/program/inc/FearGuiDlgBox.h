#pragma once

#include "simGuiActiveCtrl.h"

namespace FearGui
{
	class FGDlgBox : public SimGui::ActiveCtrl
	{
		typedef ActiveCtrl Parent;

		DECLARE_PERSISTENT(FGDlgBox);

		Resource<GFXBitmap> mTopLeft;
		Resource<GFXBitmap> mTopEdge;
		Resource<GFXBitmap> mLeftEdge;
		Resource<GFXBitmap> mBottomLeft;
		Resource<GFXBitmap> mBottomEdge;

	public:
		bool onAdd();
		void onPreRender();
		void onKeyDown(const SimGui::Event& event);
		void handleReturnKey();
		void handleEscapeKey();
		void onRender(GFXSurface* sfc, Point2I offset, const Box2I& updateRect);
		Error write(StreamIO & sio, int version, int user);
		Error read(StreamIO& sio, int version, int user);
	};
}
