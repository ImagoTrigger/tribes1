#pragma once

#include "fearGuiControl.h"

namespace FearGui
{
	class FearGuiPage : public FGControl
	{
		typedef FGControl Parent;

		DECLARE_PERSISTENT(FearGuiPage);

	protected:
		bool onAdd() override;
		DWORD onMessage(SimObject* sender, DWORD msg) override;
		void onRender(GFXSurface* sfc, Point2I offset, const Box2I& updateRect) override;
		Error write(StreamIO& sio, int version, int user) override;
		Error read(StreamIO& sio, int version, int user) override;
	};
}
