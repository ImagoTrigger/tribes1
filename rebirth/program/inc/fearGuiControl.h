#pragma once

#include "simGuiCtrl.h"

namespace FearGui
{
	class FGControl : public SimGui::Control
	{
		DECLARE_PERSISTENT(FGControl);

	protected:
		void onRender(GFXSurface* sfc, Point2I offset, const Box2I& updateRect) override;
	};
}
