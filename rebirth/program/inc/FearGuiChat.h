#pragma once

#include "FearGuiTestEdit.h"
#include "ircclient.h"

namespace FearGui
{
	class FearGuiChat : public TestEdit
	{
		// TODO: value
		static const int MaxLineCount = 5632;

		// TODO: Base type TestEdit? SimGui::TextEdit?
		typedef TestEdit Parent;

		DECLARE_PERSISTENT(FearGuiChat);

		Resource<GFXFont> msgFont;
		Resource<GFXFont> teamMsgFont;
		Resource<GFXFont> lr_msgFont;
		Resource<GFXFont> lr_teamMsgFont;

		IRCClient* mIRCClient;

		int lineCount;
		int mLowRes;
		int msgLineCount;
		BOOL mbFirstKeyPress;

		Point2F fracPos;

		int charIndex[MaxLineCount];

	public:
		bool onAdd() override;
		void onWake() override;

		void formatMessage(int width);

		void onPreRender() override;
		void onRender(GFXSurface* sfc, Point2I offset, const Box2I& updateRect) override;
		void activate();

		bool becomeFirstResponder() override;
		void onKeyDown(const SimGui::Event& event) override;
		void resize(const Point2I&, const Point2I& newExtent) override;
		void inspectWrite(Inspect* insp) override;
		void inspectRead(Inspect* insp) override;
		Error write(StreamIO& sio, int a, int b) override;
		Error read(StreamIO& sio, int a, int b) override;
	};
}
