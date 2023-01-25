#pragma once

#include "FearGuiHudCtrl.h"
#include "IRCClient.h"
#include "g_font.h"

namespace FearGui
{
	static const size_t MessageHistoryLimit = 253;

	class FearGuiChatDisplay : public HudCtrl
	{
		typedef HudCtrl Parent;

		DECLARE_PERSISTENT(FearGuiChatDisplay);

	public:
		// TODO: Values
		enum
		{
			MSG_System,
			MSG_Game,
			MSG_Chat,
			MSG_TeamChat,
			MSG_Command,
			MSG_IRC
		};

	public: //private:

		struct IRCChannelRep
		{
			DWORD dwChannelID;
			const IRCClient::Message* lpmLastRead;
		};

	public:
		struct Message
		{
			int type;
			char msg[320]; // TODO: Find actual size constant. The guess of 320 comes from FearGuiChatDisplay::newMessage method.
			char charIndex[320]; // TODO: Find actual size constant. The guess of 320 comes from FearGuiChatDisplay::newMessage method.
			int lineCount;
			int lineOffset;
		};

	public: //private:
		Vector<IRCChannelRep> mPrivateIRCMsgs;

		Resource<GFXFont> systemFont;
		Resource<GFXFont> commandFont;
		Resource<GFXFont> gameFont;
		Resource<GFXFont> msgFont;
		Resource<GFXFont> teamMsgFont;

		Resource<GFXFont> lr_systemFont;
		Resource<GFXFont> lr_commandFont;
		Resource<GFXFont> lr_gameFont;
		Resource<GFXFont> lr_msgFont;
		Resource<GFXFont> lr_teamMsgFont;

		Resource<GFXBitmap> mPageDown;
		Resource<GFXBitmap> lr_mPageDown;

		bool mLowRes;
		int prevWidth;
		int lineCount;
		int lineOffset;
		int pgUpCount;

		IRCClient* mIRCClient;

		bool mbCommanderChat;

		DWORD lastRenderTime;

		virtual GFXFont* getFont(int msgType);

		virtual bool processArg(const char* arg);
		virtual void formatMessage(int index, int width);

	protected:
		void parentResized(const Point2I&, const Point2I& newParentExtent) override;
		void resize(const Point2I&, const Point2I& newExtent) override;
		bool onAdd() override;
		void onPreRender() override;
		void onRender(GFXSurface* sfc, Point2I offset, const Box2I& updateRect) override;
		bool pointInControl(Point2I& parentCoordPoint) override;
		void onMouseDown(const SimGui::Event& event) override;
		void onMouseDragged(const SimGui::Event& event) override;
		void onMouseUp(const SimGui::Event& event) override;
		void inspectWrite(Inspect* insp) override;
		void inspectRead(Inspect* insp) override;
		Error write(StreamIO& sio, int a, int b) override;
		Error read(StreamIO& sio, int a, int b) override;

	public:
		virtual void newMessage(const char* msg, int msgType);
		virtual void clear();
		virtual void setSize(int value);
		virtual void page(int value);
	};
}
