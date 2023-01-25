#pragma once
#include "fearGlobals.h"
#include "PlayerManager.h"

namespace FearGui
{
	class CommandTeamCtrl : public FGControl
	{
		typedef FGControl Parent;

		DECLARE_PERSISTENT(CommandTeamCtrl);

		bool mLowRes;
		Point2I cellSize;
		Resource<GFXFont> hFont;
		Resource<GFXFont> lr_hFont;
		Point2I selectedCell;
		Point2I prevSelectedCell;
		PlayerManager::ClientRep** displayPlayers;
		Resource<GFXBitmap> bmpDamageLow;
		Resource<GFXBitmap> bmpDamageMed;
		Resource<GFXBitmap> bmpDamageHigh;
		Resource<GFXBitmap> bmpCMDAcknowledged;
		Resource<GFXBitmap> bmpCMDPending;
		Resource<GFXBitmap>   bmpCMDNone;
		;

		Resource<GFXBitmapArray> bma;
		Resource<GFXBitmapArray> lr_bma;
		bool active;
		Point2I size;
		int displayPlayersCount;
		PlayerManager* playerManager;
		Resource<GFXFont> hFontMuted;
		Resource<GFXFont> hFontWaitAckge;
		Resource<GFXFont> lr_hFontWaitAckge;


		// TODO:
		enum
		{
			BmpNone,
			BmpParentContinue,
			BmpParentOpen, 
			BmpParentClosed,
			BmpCount
		};

	public:
		void setLowRes(bool value);
		virtual void setSize(const Point2I& value)
		{
			this->size = value;
		}
		void onWake();
		bool onAdd();
		void setBranchSelected(PlayerManager::ClientRep* head, bool value);
		void buildPlayerDisplayList(PlayerManager::ClientRep* cl);
		void onPreRender();
		void onRenderCell(GFXSurface* sfc, Point2I offset, Point2I cell, bool, bool);
		int getSelectedPlayerId();
		Int32 getMouseCursorTag();
		void onMouseDown(const SimGui::Event& event);
	};
}
