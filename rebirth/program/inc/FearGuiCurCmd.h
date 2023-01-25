#pragma once

#include "FearGuiSimpleText.h"

namespace FearGui
{
	class FGCurrentCommand : public FGSimpleText
	{
		DECLARE_PERSISTENT(FGCurrentCommand);

		//const char* text;

	public:

		//virtual void setText(const char* value)
		//{
		//	text = value;
		//}
		void clear();
		void onRender(GFXSurface* sfc, Point2I offset, const Box2I&);
		bool mLowRes;
		Resource<GFXFont> hFont;
		Resource<GFXFont> hFontHL;
		virtual void setLowRes(const bool lores)
		{
			mLowRes = lores;
			mbLowRes = lores;
		}
	};
}
