#pragma once

#include "fearGuiControl.h"
#include "g_bitmap.h"
#include "g_font.h"

namespace FearGui
{
	enum
	{
		// TODO: Values / order
		MENU_STRING = BIT(0),
		MENU_SEPARATOR = BIT(1),
		MENU_DISABLED = BIT(2),
		MENU_CHECKED = BIT(3)
	};

	class FGPopUpMenu : public FGControl
	{
		using Event = SimGui::Event;
		
		DECLARE_PERSISTENT(FGPopUpMenu);

		struct MenuEntry
		{
			Point2I offset;
			Point2I extent;
			char* lpszText;
			bool fTargeted;
			DWORD dwTag;
			DWORD dwFlags;
		};

		Resource<GFXBitmap> rsCheck;
		Resource<GFXBitmap> rsCheckHL;
		Resource<GFXBitmap> rsCheckDS;

		Resource<GFXFont> rsFont;
		Resource<GFXFont> rsFontHL;
		Resource<GFXFont> rsFontDS;

		Point2I pos;
		Point2I ext;

		VectorPtr<MenuEntry*> menuItems;

	public:
		FGPopUpMenu();
		~FGPopUpMenu();
		// TODO: Ensure correct default values.
		void appendMenu(DWORD dwFlags, DWORD dwTag = 0, LPCTSTR lpszText = nullptr);
		void setPos(const Point2I& pos);
		void onWake() override;
		bool inHitArea(const Point2I& point);

		void onRightMouseUp(const SimGui::Event& event) override;
		void onMouseUp(const SimGui::Event& event) override;
		void onRightMouseDragged(const SimGui::Event& event) override;
		void onMouseDragged(const SimGui::Event& event) override;
		void onMouseMove(const SimGui::Event& event) override;
		void onRender(GFXSurface* sfc, Point2I, const Box2I&) override;
	};
}
