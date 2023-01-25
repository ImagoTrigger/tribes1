#pragma once

#include "fearGuiControl.h"
#include "simGuiTextEdit.h"
#include "FearHudPalTable.h"

#ifdef DrawText
#undef DrawText
#endif

namespace FearGui
{
	class TestEdit : public SimGui::TextEdit
	{

		typedef TextEdit Parent;

		DECLARE_PERSISTENT(TestEdit);

		enum
		{
			BmpCount
		};

		SimTag pbaTag;
		Resource<GFXBitmapArray> bma;
		Resource<GFXFont> hFontShadow;

	public:
		void loadBitmapArray();
		bool loseFirstResponder();
		Int32 getMouseCursorTag();
		void onKeyDown(const SimGui::Event& event);
		void setText(const char* txt);
		void onRender(GFXSurface* sfc, Point2I offset, const Box2I& updateRect);
		void DrawText(GFXSurface* sfc);
		bool onAdd();
	};
}
