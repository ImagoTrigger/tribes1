#pragma once

#include "fearGuiTextList.h"

namespace FearGui
{
	class InventoryListCtrl : public FGTextList
	{
		typedef FGTextList Parent;

	protected:

		static const int MaxInvNameLength = 256;

		typedef struct
		{
			char name[MaxInvNameLength];
			char shape[MaxInvNameLength];
			int index;
			int count;
			int cost;
			BOOL favorite;
		} InventoryRep;

		Vector<InventoryRep> inventory;

	public:
		DECLARE_PERSISTENT(InventoryListCtrl);

		bool onAdd() override;
		void onWake();
		void onPreRender();
		void onRenderCell(GFXSurface* sfc, Point2I offset, Point2I cell, bool, bool);
		bool becomeFirstResponder();
	};
}
