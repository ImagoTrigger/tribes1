#pragma once

#include "FearGuiTestEdit.h"

namespace FearGui
{
	class FGIRCTextEdit : public TestEdit
	{
		typedef TestEdit Parent;

		DECLARE_PERSISTENT(FGIRCTextEdit);

		bool mbCommandReady;

	public:
		void onKeyDown(const SimGui::Event & event);
		void getIRCText(char* buf);
		bool becomeFirstResponder();
		bool loseFirstResponder();
		bool onAdd();
		void onWake();
		virtual bool isCommandReady() const
		{
			return this->mbCommandReady;
		}
	};
}
