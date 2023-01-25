#pragma once

#include "fearGuiHudCtrl.h"
#include "FearGuiShellPal.h"

namespace FearGui
{
	class FearGuiBox : public FGControl
	{
		typedef FGControl Parent;
		
		DECLARE_PERSISTENT(FearGuiBox);

		bool mGhosted;

	public:
		void onRender(GFXSurface* sfc, Point2I offset, const Box2I& updateRect) override;
		bool onAdd() override;

		void setGhosted(bool value)
		{
			mGhosted = value;
		}
	};
}
