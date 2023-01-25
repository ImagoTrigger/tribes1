#pragma once

#include "simGuiTextEdit.h"
#include <Timer.h>

namespace FearGui
{
	class FGIRCChannelList;

	class FGIRCActiveTextEdit : public SimGui::TextEdit
	{
		typedef SimGui::TextEdit Parent;

		Timer timer;
		bool fListGenerated;
		FGIRCChannelList* objList;

	public:
		FGIRCActiveTextEdit();
		~FGIRCActiveTextEdit();
		void onWake() override;
		void associateList(FGIRCChannelList* list);
		void onPreRender() override;
		void onKeyDown(const SimGui::Event& event) override;

		DECLARE_PERSISTENT(FGIRCActiveTextEdit);
	};
}
