#pragma once

#include "g_pal.h"
#include "simGuiCtrl.h"

namespace FearGui
{
	enum HudColor
	{
		_BLACK,
		_RED,
		_GREEN_40,
		_GREEN_78,
		_GREEN_132,
		_GREEN,
		_BLUE,
		_YELLOW,
		_BLUE_OUTLINE,
		_BLUE_HILITE,
		_WHITE,
		_NUM_HUD_COLORS
	};

	// TODO:
	enum
	{
		BLACK = 1,
		RED = 243,
		GREEN_40 = 247,
		GREEN_78 = 140,
		GREEN_132 = 200,
		GREEN = 252,
		BLUE = 216,
		YELLOW = 242,
		BLUE_OUTLINE = 194,
		BLUE_HILITE = 251,
		WHITE = 255
	};

	struct HudColors
	{
		HudColor color;

		BYTE r;
		BYTE g;
		BYTE b;

		int colorIdx;
	};
	extern HudColors gPaletteColors[_NUM_HUD_COLORS];

	class FGHPaletteTable : public SimGui::Control
	{
		typedef Control Parent;

		DECLARE_PERSISTENT(FGHPaletteTable);

		HudColors gHudColors[_NUM_HUD_COLORS];

		void InitializeTable(GFXPalette* pal);

	public:
		void onRender(GFXSurface * sfc, Point2I, const Box2I &) override;
	};
}
