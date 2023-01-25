#pragma once

#include "FearGuiCombo.h"

namespace FearGui
{
	class FGStandardComboBox;

	class StandardListCtrl : public FGComboList
	{
		typedef FGComboList Parent;

	public:
		bool mbSortEntries;
		Vector<EntryRep> entries;
		VectorPtr<EntryRep*> entryPtrs;

	public:
		DECLARE_PERSISTENT(StandardListCtrl);

		void addEntry(const char* buf, int id);
		void deleteEntry(int id);
		int findEntry(const char* buf);
		void clear();
		int getSelectedEntry();
		void setSelectedEntry(int id);
		bool onAdd() override;
		bool cellSelected(Point2I cell) override;
		const char* getCellText(GFXSurface*, const Point2I& cell, const Point2I&, const Point2I&) override;
		const char* getSelectedText();
		void selectPrev();
		void selectNext();

		inline void setSort(bool value)
		{
			mbSortEntries = value;
		}
	};

	class FGStandardComboBox : public FGComboBox
	{
		typedef FGComboBox Parent;

	protected:
		Resource<GFXBitmap> mTitleBMP;
		Resource<GFXBitmap> mTitleGhostBMP;

	public:
		void setSort(bool value);

		bool onAdd() override;
		void onMouseDown(const SimGui::Event& event) override;
		void openPopUpCtrl() override;
		void closePopUpCtrl() override;
		void updateFromArrayCtrl() override;
		void inspectWrite(Inspect* insp) override;
		void inspectRead(Inspect* insp) override;
		Persistent::Base::Error write(StreamIO& sio, int version, int user) override;
		Persistent::Base::Error read(StreamIO& sio, int version, int user) override;

		DECLARE_PERSISTENT(FGStandardComboBox);
	};

	class FGStandardPopUp : public FGComboPopUp
	{
		typedef FGComboPopUp Parent;

	public:
		FGStandardPopUp(FGStandardComboBox* parent) : Parent(parent)
		{
		}

		void setSort(bool value);

		bool onAdd() override;
	};
}
