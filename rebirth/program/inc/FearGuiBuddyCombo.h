#pragma once

#include "FearGuiStandardCombo.h"

namespace FearGui
{
	class FGBuddyComboBox : public FGStandardComboBox
	{
		typedef FGStandardComboBox Parent;

	public:
		bool onAdd();
		void onRender(GFXSurface* sfc, Point2I offset, const Box2I& updateRect);

		DECLARE_PERSISTENT(FGBuddyComboBox);
	};
}
