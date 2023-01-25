#pragma once

#include "SimGuiTsCtrl.h"
#include "timer.h"
#include <stdexcept>
#include "fearGuiControl.h"

namespace FearGui
{
	///
	///	The TV window in the Commander GUI.
	///
	class CMDObserve : public FGControl
	{
		// TODO: Guess FGControl
		typedef FGControl Parent;
		
		DECLARE_PERSISTENT(CMDObserve);
		
		SimGui::TSControl* ts_control;
		bool fObject;
		int iObservedID;

		Point2I ctl_offset;
		Point2I ctl_extent;

		Point2I eff_offset;
		Point2I eff_extent;

		struct
		{
			int iMin;
			int iMax;
			int iCur;
			int iInc;
			RealF rSPF;
		} snowinfo;

		bool fTVSnowDone;
		int iEnergyBarTick;
		int iHealthBarTick;
		bool fInfoBarsGrown;
		bool fUpdateInfo;
		bool fTVStartUpDone;
		bool fTVRollDone;

		Timer snow_timer;
		Timer info_timer;

		virtual void doTVStartUp();
		virtual void doTVSnow(GFXSurface* sfc, Point2I offset);
		virtual void doTVSnowFadeOut(GFXSurface* sfc, Point2I offset);
		virtual void growInfoBars(int iHealth, int iEnergy);

	protected:
		void onWake() override;
		void onPreRender() override;
		void onRender(GFXSurface* sfc, Point2I offset, const Box2I& updateRect) override;

	public:
		CMDObserve();
		virtual ~CMDObserve();
		
		virtual bool observePlayer(int iPlayerID);
		virtual void activate(bool fActivate);

	};
}
