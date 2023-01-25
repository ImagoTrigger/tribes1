#pragma once

#include "FearGuiCombo.h"

namespace FearGui
{
	class PlayerListCtrl : public FGComboList
	{
		typedef FGComboList Parent;

		static const int MaxClientNameLength = 256;

	public:
		typedef FGComboList::EntryRep ClientRep;

	private:
		Vector<ClientRep> players;
		VectorPtr<ClientRep*> playerPtrs;

	public:
		void addEntry(const char* buf, int id);
		void deleteEntry(int id);
		void clear();
		int getSelectedEntry();
		void setSelectedEntry(int id);
		bool onAdd();
		bool cellSelected(Point2I cell);
		const char* getCellText(GFXSurface*, const Point2I& cell, const Point2I&, const Point2I&);
		const char* getSelectedPlayer();

		DECLARE_PERSISTENT(PlayerListCtrl);
	};
}
