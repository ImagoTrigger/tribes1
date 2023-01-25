#pragma once

#include "simGuiTextList.h"

namespace FearGui
{
	class FGTextList : public SimGui::TextList
	{
		typedef TextList Parent;

	protected:
		Resource<GFXFont> hFontDisabled;

	public:
		FGTextList();
		~FGTextList();
		Int32 getSelectedPos();
		void setSelection(Int32 iPos);
		bool cellSelected(Point2I cell) override;
		bool onAdd() override;
		void onWake() override;
		void onRenderCell(GFXSurface* sfc, Point2I offset, Point2I cell, bool selected, bool mouseOver) override;

		DECLARE_PERSISTENT(FGTextList);
	};
}
