#pragma once

#include "FearGuiStandardCombo.h"

namespace FearGui
{
	class FGPlayerComboBox : public FGStandardComboBox
	{
		typedef FGStandardComboBox Parent;

	public:

		bool onAdd();
		void openPopUpCtrl();
		void updateFromArrayCtrl();

		DECLARE_PERSISTENT(FGPlayerComboBox);
	};

	class FGPlayerPopUp : public FGStandardPopUp
	{
		typedef FGStandardPopUp Parent;

	public:
		FGPlayerPopUp(FGPlayerComboBox* parent) : Parent(parent)
		{
		}
		bool onAdd();
	};
}
