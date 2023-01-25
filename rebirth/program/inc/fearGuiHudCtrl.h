#pragma once

#include "fearGuiControl.h"

namespace FearGui
{
	class HudCtrl : public SimGui::Control
	{
		typedef SimGui::Control Parent;

		bool stateOver;
		bool stateDragging;
		bool statePressed;

	protected:
		Point2F fracPos;

	private:
		Point2I hitPt;

		// TODO: static const? some value? Is this set anywhere?
		float SnapDistance;

	protected:


		virtual void snap();

	public:
		HudCtrl();
		virtual ~HudCtrl();

		void onMouseDown(const SimGui::Event& event) override;
		void onMouseDragged(const SimGui::Event& event) override;
		void onMouseUp(const SimGui::Event& event) override;
		void parentResized(const Point2I&, const Point2I& newParentExtent) override;
		void resize(const Point2I&, const Point2I& newExtent) override;
		bool onAdd() override;
		void onRender(GFXSurface* sfc, Point2I offset, const Box2I& updateRect) override;
		void onRemove() override;
		virtual void detach();
		void onWake() override;
		virtual bool onSimActionEvent(const SimActionEvent* event);
		bool processEvent(const SimEvent* event);
		Error write(StreamIO& sio, int a, int b) override;
		Error read(StreamIO& sio, int a, int b) override;

		DECLARE_PERSISTENT(HudCtrl);
	};
}
