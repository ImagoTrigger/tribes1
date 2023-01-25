#pragma once

#include "FearGuiPage.h"
#include "SimGuiTextFormat.h"

// TODO: Guess ..
const size_t MAX_NUM_OBJECTIVES = 24;

namespace FearGui
{
	class FGHCommandObjectivePage : public FearGuiPage
	{
		typedef FearGuiPage Parent;

		DECLARE_PERSISTENT(FGHCommandObjectivePage);

		SimGui::TextFormat* objectives[MAX_NUM_OBJECTIVES];

	protected:
		bool onAdd() override;
		void onWake() override;
		void onPreRender() override;
		void onRender(GFXSurface* sfc, Point2I offset, const Box2I& updateRect) override;

	public:
		FGHCommandObjectivePage();
		virtual ~FGHCommandObjectivePage();

		void newObjective(int index, const char* text);
	};
}
