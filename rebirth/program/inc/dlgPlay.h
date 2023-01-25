#pragma once

#include "SimGuiDelegate.h"
#include "FearPlayerPSC.h"

class SimPalette;

namespace FearGui
{
	class TSCommander;
}

namespace SimGui
{
	class playDelegate : public Delegate
	{
		typedef Delegate Parent;

		DECLARE_PERSISTENT(playDelegate);

		bool hudListVisible;
		bool gameActive;
		int curMode;
		Control* curGui;
		SimPalette* currentPalette;
		Resource<GFXPalette> hPal;
		Control* commandGui;
		int mShellPage;
		bool mbCommandMode;
		bool scoresVisible;

		Resource<SimActionMap> actionEventMap;
		Resource<SimActionMap> playEventMap;
		Resource<SimActionMap> commandEventMap;

		FearGui::TSCommander* tsc;

		WORD shoppingList[PlayerPSC::ItemShoppingListWords];
		
		virtual void setHudListVisible(bool vis);		
		
		bool onSimActionEvent(const SimActionEvent* event);
		virtual void updateTeamEnergy();

	protected:
		void onDeleteNotify(SimObject* obj) override;
		bool onAdd() override;
		void onNewContentControl(Control* oldGui, Control* newGui) override;
		void onLoseDelegation() override;
		void preRender() override;
		bool processEvent(const SimEvent* event) override;
		DWORD onMessage(SimObject* sender, DWORD msg) override;

	public:
		virtual void setCurrentGuiMode(int newMode);
		virtual void setScoresVisible(bool vis);
		virtual void activate();
		virtual void reset();
	};
}
