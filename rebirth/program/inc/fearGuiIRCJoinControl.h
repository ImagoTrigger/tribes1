#pragma once
#include "fearGuiControl.h"

namespace FearGui
{
	class FGIRCJoinControl : public FGControl
	{
		typedef FGControl Parent;

		DECLARE_PERSISTENT(FGIRCJoinControl);

	public:

		struct Channel : public GameBase::GameBaseData
		{
			const char* name;
			const char* topic;
		};

		FGIRCJoinControl();
		~FGIRCJoinControl();
		void onWake();
		void getDefaultChannelList();
		DWORD onMessage(SimObject* obj, DWORD dwMsg);
		bool onSimMessageEvent(const SimMessageEvent* event);
		bool processEvent(const SimEvent* event);
	};
}
