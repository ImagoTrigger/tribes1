#pragma once

#include "simGuiComboBox.h"
#include "fearGuiTextList.h"

namespace FearGui
{
	class FGComboBox;
	class FGComboPopUp;

	class FGComboList : public SimGui::ArrayCtrl
	{
		typedef SimGui::ArrayCtrl Parent;

		static bool mbCconsoleFunctionsAdded;

	public:
		static const int MaxEntryNameLength = 256;

		struct EntryRep
		{
			int consoleIndex;
			char name[MaxEntryNameLength + 1];
		};

	protected:

		Resource<GFXFont> hFont;
		Resource<GFXFont> hFontHL;
		Resource<GFXFont> hFontSel;
		Resource<GFXFont> hFontShadow;

	public:
		bool onAdd() override;
		void onPreRender() override;
		bool becomeFirstResponder() override;

		virtual void addEntry(const char* buf, int id);
		virtual void deleteEntry(int id);
		virtual int findEntry(const char* buf);
		virtual void clear();
		virtual int getSelectedEntry();
		virtual void setSelectedEntry(int id);
		virtual const char* getSelectedText();
		virtual void selectPrev();
		virtual void selectNext();
		virtual const char* getCellText(GFXSurface*, const Point2I& cell, const Point2I&, const Point2I&) = 0;
		virtual void onRenderCell(GFXSurface* sfc, Point2I offset, Point2I cell, bool selected, bool mouseOver);
	};

	class FGComboBox : public SimGui::ComboBox
	{
		typedef SimGui::ComboBox Parent;
		typedef SimGui::SimpleText GrandParent;

	public:
		static const size_t BMP_Standard = 0;
		static const size_t BMP_MouseOverStandard = 1;
		static const size_t BMP_Pressed = 2;
		static const size_t BMP_Ghosted = 3;
		//static const size_t BMP_BackgroundOn = 6;
		//static const size_t BMP_BackgroundOff = 7;

		static const size_t BMP_Count = 6;

	protected:
		char mBitmapRootName[256];

		Resource<GFXBitmap> mBitmaps[BMP_Count * 2];

		Resource<GFXFont> hFontShadow;
		Resource<GFXFont> hFontTitle;
		Resource<GFXFont> hFontTitleShadow;
		Resource<GFXFont> hFontTitleDisabled;

	protected:
		Int32 getMouseCursorTag() override;
		bool onAdd() override;
		void onRender(GFXSurface* sfc, Point2I offset, const Box2I& updateRect) override;
		void inspectWrite(Inspect* insp) override;
		void inspectRead(Inspect* insp) override;
		Error write(StreamIO& sio, int version, int user) override;
		Error read(StreamIO& sio, int version, int user) override;

	public:
		virtual void setBitmaps();
		virtual int getSelectedEntry();
		virtual void setSelectedEntry(int id);
		virtual const char* getSelectedText();
		virtual Point2I getSelected();
		virtual void drawText(GFXSurface* sfc, GFXFont* font, const char* text, Point2I& offset, Point2I& dest);
		virtual void setSelected(Point2I& cell);
		virtual void addEntry(const char* buf, int id);
		virtual int findEntry(const char* buf);
		virtual void clear();
		virtual void deleteEntry(int id);
		virtual void selectPrev();
		virtual void selectNext();
	};

	class FGComboPopUp : public SimGui::ComboPopUp
	{
		typedef SimGui::ComboPopUp Parent;
		typedef SimGui::Control GrandParent;

		virtual void setBoarder();

	protected:
		bool onAdd() override;
		void setDim(Int32 w, Int32 hMin, Int32 hMax) override;
		Int32 getMouseCursorTag() override;

	public:
		FGComboPopUp(FGComboBox* parent) : Parent(parent)
		{
		}

		virtual void setSelected(Point2I& cell);
		virtual Point2I getSelected();
	};
}
