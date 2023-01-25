#pragma once

#include "simGuiSimpleText.h"

namespace FearGui
{
	class CFGButton : public SimGui::SimpleText
	{
		typedef SimpleText Parent;

		DECLARE_PERSISTENT(CFGButton);

		Resource<GFXFont> hFontShadow;

		Resource<GFXBitmap> mDefaultBMP;
		Resource<GFXBitmap> mGhostedBMP;
		Resource<GFXBitmap> mPressedBMP;
		Resource<GFXBitmap> mShiftIcon;
		Resource<GFXBitmap> mAltIcon;
		Resource<GFXBitmap> mCtrlIcon;
		bool mbDefine;
		// TODO: Length
		char mBinding[256];
		// TODO: Length
		char mActionMap[256];
		SimTag mMakeAction;
		SimTag mMakeValue;
		SimTag mBreakAction;
		SimTag mBreakValue;
		Int32 mFlags;

		char ascii;
		BYTE modifier;

		SimInputEvent boundEvent;

	protected:
		bool onAdd() override;
		void inspectWrite(Inspect* insp) override;
		void inspectRead(Inspect* insp) override;
		Error write(StreamIO& sio, int version, int user) override;
		Error read(StreamIO& sio, int version, int user) override;
		Int32 getMouseCursorTag() override;
		void onAction() override;
		void onPreRender() override;
		void onRender(GFXSurface* sfc, Point2I offset, const Box2I&) override;

	public:
		CFGButton();

		static float getMouseSensitivity(const char* actionMapName);
		static bool getMouseXAxisFlip(const char* actionMapName);
		static bool getMouseYAxisFlip(const char* actionMapName);
		static bool getMouseAxisFlip(const char* actionMapName, bool xAxis);

		virtual bool bindingConflict(const SimInputEvent* event);
		virtual void removeBinding();
		virtual void newBinding(const SimInputEvent* event);
		virtual const char* findActionBinding(SimInputEvent* destEvent);
		virtual void refreshBinding();
	};
}
