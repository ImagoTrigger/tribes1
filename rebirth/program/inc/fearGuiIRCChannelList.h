#pragma once

#include "FearGuiArrayCtrl.h"

namespace FearGui
{
	class FGIRCChannelList : public FGArrayCtrl
	{
		typedef FGArrayCtrl Parent;

	public:
		struct Channel
		{
			const char* lpszName;
			const char* lpszTopic;
			bool fOwnsStrings;
		};

	private:

		VectorPtr<Channel*> channels;
		VectorPtr<Channel*> show;

	public:
		FGIRCChannelList();
		~FGIRCChannelList();
		bool cellSelectable(const Point2I& cell);
		bool cellSelected(Point2I cell);
		bool onAdd() override;
		void onWake() override;
		void addChannel(const char* lpszName, const char* lpszTopic, bool fOwnsStrings);
		const char* getSelectedChannel() const;
		void showMatches(const char* lpszText);
		void clear();
		void sort();
		char* getCellText(GFXSurface*, const Point2I& cell, const Point2I&, const Point2I&);
		void onPreRender() override;
		void onRenderCell(GFXSurface* sfc, Point2I offset, Point2I cell, bool sel, bool mouseOver) override;

		DECLARE_PERSISTENT(FGIRCChannelList);
	};
}
