#pragma once

#include "simGuiDelegate.h"

namespace SimGui
{
	class JoinGameDelegate : public Delegate
	{
		typedef Delegate Parent;

		DECLARE_PERSISTENT(JoinGameDelegate);
		
		Control* curGui;
		int mCurFilter;
		bool mbMasterTimedOut;

	protected:		
		void onNewContentControl(Control*, Control* newGui) override;
		void onLoseDelegation() override;
		DWORD onMessage(SimObject* sender, DWORD msg) override;

	public:

		virtual bool verifyServer();
		virtual bool verifyMasterMOTD();
		virtual void masterTimeout(const char* address);
		virtual void updatePingLists(int numToPing, int numPinged, bool firstPhase);
		virtual void queryFinished();

	};
}
