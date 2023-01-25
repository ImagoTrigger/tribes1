#pragma once

#include "SimGuiCtrl.h"
#include "FearCSDelegate.h"

namespace SimGui
{
	class JoinGameDelegate;
}


namespace FearGui
{
	class ServerListCtrl : public SimGui::Control
	{
		typedef Control Parent;
		
		friend class FearCSDelegate;
		friend class SimGui::JoinGameDelegate;

		DECLARE_PERSISTENT(ServerListCtrl);

		static int prefColumnToSort;
		static bool prefSortAscending;
		static int prefColumnToSortSecond;
		static bool prefSortAscendingSecond;

		static int mConnectionHi;
		static int mConnectionLo;

		bool sortAscending;		
		int columnToSort;
		
		bool sortAscendingSecond;
		int columnToSortSecond;
		
		ServerListCtrl();

		virtual void readDisplayTable();
		virtual void writeScriptFile();
		virtual void serverTimeout(const char* address);
		virtual bool isNeverPing(const char* address);
		virtual void setNeverPing(const char* address, bool value);
		virtual void rebuildNeverPingList();
		virtual bool isFavorite(const char* address);
		virtual void setFavorite(const char* address, bool value);
		
		virtual void removeCurrentServer();
		virtual void updatePingList(const char* address);
		virtual void gotPingInfo(const char* address, const char* name, UInt16 version, int ping);
		virtual void gotGameInfo(FearCSDelegate::ServerInfo* info);
		virtual FearCSDelegate::ServerInfo* getServerSelected(bool& infoAvail);
		virtual void writeDisplayTable();
		virtual bool cellSelectable(const Point2I& cell);
		virtual bool cellSelected(Point2I cell);
		virtual void updateCurFilter();
		virtual bool findBuddy(FearCSDelegate::ServerInfo* info, const char* buddy);
		virtual bool findBuddy(FearCSDelegate::ServerInfo* info);
		virtual bool filterServer(FearCSDelegate::ServerInfo* info);
		virtual void refreshList();
		virtual void rebuildList();
		virtual bool refreshVisible();
		virtual void rebuildFinished(bool bMasterTimedOut);
		virtual void rebuildCancel();
		virtual char* getCellText(GFXSurface* sfc, const Point2I& cell, const Point2I& cellOffset, const Point2I& cellExtent);

	protected:
		void onMouseDown(const SimGui::Event& event) override;
		void onKeyDown(const SimGui::Event& event) override;
		void onMouseUp(const SimGui::Event& event) override;
		Int32 getMouseCursorTag() override;
		Int32 getHelpTag(float elapsedTime) override;
		bool onAdd() override;
		void onWake() override;
		void onPreRender() override;

	public:
		virtual void addGameServer(int argc, const char * argv[]);
	};
}
