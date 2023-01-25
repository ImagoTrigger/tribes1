#pragma once

#include "fearGuiControl.h"
#include "simGuiSimpleText.h"

namespace FearGui
{
	class FGSimpleText : public SimGui::SimpleText
	{
		typedef SimpleText Parent;

		DECLARE_PERSISTENT(FGSimpleText);

	protected:
		Resource<GFXFont> hFontShadow;
		Resource<GFXFont> lrFont;
		Resource<GFXFont> lrFontHL;
		Resource<GFXFont> lrFontDisabled;
		Resource<GFXFont> lrFontShadow;
		bool mbLowRes;

	public:
		
		bool onAdd(void);
		void setText(const char* txt);
		void onRender(GFXSurface* sfc, Point2I offset, const Box2I&);

		inline bool becomeFirstResponder() override
		{
			return false;
		}
	};
}

