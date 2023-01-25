#pragma once

#include "FearGuiInvList.h"
#include "FearGuiArrayCtrl.h"

namespace FearGui
{
	class FGHInventory : public InventoryListCtrl
	{
		typedef InventoryListCtrl Parent;
		//typedef FGTextList Grandparent;

		DECLARE_PERSISTENT(FGHInventory);

		Resource<GFXBitmap> statusFavorite;

		int numColumns;
		FGArrayCtrl::ColumnInfo** columnInfo;

		Point2I prevSelected;

	public:
		bool onAdd() override;
		void onWake() override;
		void onPreRender() override;
		char* getCellText(GFXSurface* sfc, const Point2I& cell, const Point2I& cellOffset, const Point2I& cellExtent);
		void dropSelected();
		void useSelected();
		void sellSelected();
		void setFavorites();
		void onMouseDown(const SimGui::Event& event) override;
		bool cellSelected(Point2I cell) override;
	};

	class FGHBuySell : public InventoryListCtrl
	{
		typedef InventoryListCtrl Parent;
		typedef FGTextList Grandparent;

		DECLARE_PERSISTENT(FGHBuySell);

		Resource<GFXBitmap> statusFavorite;

		int numColumns;
		FGArrayCtrl::ColumnInfo** columnInfo;

		Point2I prevSelected;

	public:
		bool onAdd() override;
		void onWake() override;
		void onPreRender() override;
		char* getCellText(GFXSurface* sfc, const Point2I& cell, const Point2I& cellOffset, const Point2I& cellExtent);
		void buySelected();
		void buyFavorites();
		void onMouseDown(const SimGui::Event& event) override;
		bool cellSelected(Point2I cell) override;
	};
}
