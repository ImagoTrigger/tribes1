#pragma once

#include "fearGuiArrayCtrl.h"
#include "IRCClient.h"

namespace FearGui
{
	typedef SimGui::Event Event;

	class FGIRCNicknames : public FGArrayCtrl
	{
		typedef FGArrayCtrl Parent;
		typedef SimGui::ArrayCtrl Grandparent;

		DECLARE_PERSISTENT(FGIRCNicknames);

	public:
		struct NickRep
		{
			char* nick;
			BitSet32 status;
		};

	private:
		Resource<GFXBitmap> mAwayBMP;
		Resource<GFXBitmap> mIgnoreBMP;
		Resource<GFXBitmap> mLockBMP;
		Resource<GFXBitmap> mMesgBMP;
		Resource<GFXBitmap> mOperBMP;
		Resource<GFXBitmap> mSpecBMP;
		Resource<GFXBitmap> mSpkrBMP;

		IRCClient* mIRCClient;
		Point2I prevSelected;

		Vector<NickRep> entries;
		VectorPtr<NickRep*> entryPtrs;

	public:
		bool onAdd();
		void onWake();
		void onPreRender();
		void onRenderCell(GFXSurface* sfc, Point2I offset, Point2I cell, bool sel, bool mouseOver);
		void onRender(GFXSurface* sfc, Point2I offset, const Box2I& updateRect);
		char* getCellText(GFXSurface*, const Point2I& cell, const Point2I&, const Point2I&);
		const char* getSelectedText();

		void onRightMouseDown(const Event& event);
		void onMouseDown(const Event& event);
		void onRightMouseUp(const Event& event);
	};
}
