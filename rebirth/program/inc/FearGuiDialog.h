#pragma once

namespace FearGui
{
	class FearGuiDialog : public FGControl
	{
		typedef FGControl Parent;

		DECLARE_PERSISTENT(FearGuiDialog);

		Point2I fixedSize;

	public:
		bool becomeFirstResponder();
		bool loseFirstResponder();
		void onWake();
		bool onAdd();
		void parentResized(const Point2I&, const Point2I& newParentExtent);
		void onRender(GFXSurface* sfc, Point2I offset, const Box2I& updateRect);
		void inspectWrite(Inspect* insp);
		void inspectRead(Inspect* insp);
		Persistent::Base::Error write(StreamIO& sio, int a, int b);
		Persistent::Base::Error read(StreamIO& sio, int a, int b);
	};
}
