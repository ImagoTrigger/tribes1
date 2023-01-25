#pragma once
#include "simGuiArrayCtrl.h"
#include "g_font.h"
#include "FearGuiShellPal.h"

namespace FearGui
{
	class FGArrayCtrl : public SimGui::ArrayCtrl
	{
		typedef ArrayCtrl Parent;

		//DECLARE_PERSISTENT(FGArrayCtrl);

		// TODO:
		enum
		{
			BmpDivide,
			BmpDivideNA,
			BmpSortUp,
			BmpSortUpNA,
			BmpSortDown,
			BmpSortDownNA,
			BmpCount
		};

	protected:
		SimTag pbaTag;
		Resource<GFXBitmapArray> bma;
		int columnToResize;
		bool columnsDualSortable;
		bool refresh;
		int columnToSort;
		bool columnsResizeable;
		bool columnsSortable;
		int numColumns;
		Point2I dragPoint;
		Point2I startPoint;
		bool sortAscending;
		Point2I startExtent;
		int columnToSortSecond;
		int sortAscendingSecond;
		
		Resource<GFXFont> headerFont;
		Resource<GFXFont> headerFontHL;
		Resource<GFXFont> headerFontNA;
		Resource<GFXFont> headerFontShadow;

		Resource<GFXFont> hFont;
		Resource<GFXFont> hFontHL;
		Resource<GFXFont> hFontNA;
		Resource<GFXFont> hFontMO;

	public:
		struct ColumnInfo
		{
			SimTag headerTag;
			int origPosition;
			int unk;
			int width;
			int maxWidth;
			bool active;
			int unk3;
			int(__cdecl * sortDescend)(const void* a, const void* b);
			int(__cdecl * sortAscend)(const void* a, const void* b);
		};

		ColumnInfo** columnInfo;

		static bool mbCconsoleFunctionsAdded;

		void loadBitmapArray();
		Int32 getMouseCursorTag();
		void onMouseDown(const SimGui::Event& event);
		void onRightMouseDown(const SimGui::Event& event);
		void onMouseDragged(const SimGui::Event& event);
		void onMouseUp(const SimGui::Event& event);

		void addEntry(const char* buf, int id);
		void deleteEntry(int id);
		int findEntry(const char* buf);
		void clear();
		int getSelectedEntry();
		void setSelectedEntry(int id);
		const char* getSelectedText();
		bool onAdd();
		void onWake();
		// TODO: Default values.
		void drawInfoText(GFXSurface* sfc, GFXFont* font, const char* text, Point2I& offset, Point2I& dest, bool shadow = false, bool centered = false);
		void onPreRender();
		void onRenderColumnHeaders(GFXSurface* sfc, Point2I offset, Point2I parentOffset, Point2I headerDim);
		bool cellSelectable(const Point2I& cell)
		{
			// TODO:
			return false;
		}

		char* getCellText(GFXSurface*, const Point2I& cell, const Point2I& draw_offset, const Point2I& point2_i1)
		{
			return "TODO";
		}

		void onRenderCell(GFXSurface* sfc, Point2I offset, Point2I cell, bool sel, bool mouseOver);
		void onRender(GFXSurface* sfc, Point2I offset, const Box2I& updateRect);
	};
}
