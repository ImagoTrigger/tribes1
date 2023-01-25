#pragma once

#include "SimGuiMatrixCtrl.h"
#include "FearGuiShellPal.h"

namespace FearGui
{
	class FearGuiScrollCtrl : public SimGui::MatrixCtrl
	{
		typedef MatrixCtrl Parent;

	public:
		enum
		{
			BMP_TopLeft_DF,
			BMP_TopEdge_DF,
			BMP_TopRight_DF,
			BMP_RightEdge_DF,
			BMP_BottomRight_DF,
			BMP_BottomEdge_DF,
			BMP_BottomLeft_DF,
			BMP_LeftEdge_DF,
			BMP_Count
		};
	private:

		Resource<GFXBitmap> mBitmaps[BMP_Count];

	public:

		bool onAdd() override;
		Int32 getMouseCursorTag(void) override;
		void drawVScrollBar(GFXSurface* sfc, const Point2I& offset);
		void drawHScrollBar(GFXSurface* sfc, const Point2I& offset);
		void drawBorder(GFXSurface* sfc, const Point2I& offset);

		void inspectWrite(Inspect* insp) override;
		void inspectRead(Inspect* insp) override;
		Error write(StreamIO& sio, int a, int b) override;
		Error read(StreamIO& sio, int a, int b) override;

		DECLARE_PERSISTENT(FearGuiScrollCtrl);

		inline void setBorderThickness(Int32 value)
		{
			borderThickness = value;
		}

		inline bool becomeFirstResponder() override
		{
			return false;
		}
	};
}
