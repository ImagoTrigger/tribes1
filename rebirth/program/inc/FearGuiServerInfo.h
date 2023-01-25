#pragma once

#include "simGuiArrayCtrl.h"

namespace FearGui
{
	class ServerInfoCtrl : public SimGui::ArrayCtrl
	{
		typedef SimGui::ArrayCtrl Parent;
		typedef SimGui::ActiveCtrl Grandparent;

		Resource<GFXFont> hFont;
		Resource<GFXFont> hFontHL;

		enum {
			MaxColumns = 16,
		};

		int teamTabStops[MaxColumns];
		int playerTabStops[MaxColumns];

		FearCSDelegate::ServerInfo* mServer;

	public:
		bool onAdd() override;
		void onWake() override;
		void setServerInfo(FearCSDelegate::ServerInfo* info);
		void onRenderCell(GFXSurface* sfc, Point2I offset, Point2I cell, bool, bool);
		void onRender(GFXSurface* sfc, Point2I offset, const Box2I& updateRect);

		DECLARE_PERSISTENT(ServerInfoCtrl);
	};
}
