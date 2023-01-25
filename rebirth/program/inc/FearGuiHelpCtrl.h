#pragma once

#include "fearGuiTextFormat.h"
#include "simGuiHelpCtrl.h"

namespace FearGui
{
	class FGHelpCtrl : public SimGui::HelpCtrl
	{
		typedef HelpCtrl Parent;

		DECLARE_PERSISTENT(FGHelpCtrl);

		const char* mHelpText;
		SimTag mHelpTag;

		FGTextFormat helpPanel;

	protected:
		void setHelpTag(Int32 helpTag, float timeElapsed, bool mouseClicked) override;
		void setHelpText(const char* text, float, bool) override;
		void render(GFXSurface* sfc) override;
		
	public:
		FGHelpCtrl();
		virtual ~FGHelpCtrl();
	};
}
