#pragma once

#include "simGuiPaletteCtrl.h"

namespace FearGui
{
	class FGPaletteCtrl : public SimGui::PaletteCtrl
	{
		typedef PaletteCtrl Parent;

		DECLARE_PERSISTENT(FGPaletteCtrl);

	public:
		void loadPalette() override;
	};
}
