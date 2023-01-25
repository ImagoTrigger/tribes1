#pragma once
#include "SimGuiTsCtrl.h"
#include "timer.h"
#include "simResource.h"

namespace FearGui
{
	class ShapeView : public SimGui::TSControl
	{
		typedef TSControl Parent;

		DECLARE_PERSISTENT(ShapeView);

		// TODO length
		char szShape[256];
		bool active;

		TSCamera* camera;
		TSSceneLighting* scene;
		TSLight* light;
		Resource<TSShape> rsShape;
		TSShapeInstance* instance;
		RealF rDist;
		EulerF rotation;
		bool fAutoRotate;
		bool fLeftMouseDown;
		bool fRightMouseDown;
		Timer timer;
		Point2I last;
		Point3F center;
		RealF rMinDist;
		RealF rDefDist;
		RealF rMaxDist;

		TSRenderContext context;
		TS::PointArray points;

		

	public:
		ShapeView();
		virtual ~ShapeView();
		bool onAdd();
		void onRemove();
		void onWake();
		void loadShape(const char* lpszName);
		Int32 getMouseCursorTag();
		void onRightMouseDown(const SimGui::Event& event);
		void onMouseDown(const SimGui::Event& event);
		void onRightMouseUp(const SimGui::Event& event);
		void onMouseUp(const SimGui::Event& event);
		void onRightMouseDragged(const SimGui::Event& event);
		void onMouseDragged(const SimGui::Event& event);
		bool becomeFirstResponder();
		void onPreRender();
		void onRender(GFXSurface* sfc, Point2I offset, const Box2I&);
		void inspectRead(Inspect* inspect);
		void inspectWrite(Inspect* inspect);
		Persistent::Base::Error read(StreamIO & sio, int iVer, int iUsr);
		Persistent::Base::Error write(StreamIO& sio, int iVer, int iUsr);
		float getFarPlane();
	};
}
