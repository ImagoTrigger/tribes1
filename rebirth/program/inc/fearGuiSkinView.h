#pragma once

#include "simGuiActiveCtrl.h"
#include "ts_camera.h"
#include "ts_light.h"
#include "ts_pointArray.h"
#include "ts_shapeInst.h"

namespace FearGui
{
	class SkinView : public SimGui::ActiveCtrl
	{
		typedef ActiveCtrl Parent;

		static bool sm_discoBoogie;

		enum
		{
			Light,
			Medium,
			Heavy,
			NumArmors
		};

		TS::PerspectiveCamera* camera;
		TS::SceneLighting* scene;
		TS::Light* light;
		Resource<TS::Shape> rsShape;
		TS::ShapeInstance* instance;
		float rDist;
		EulerF rotation;
		bool fLeftMouseDown;
		bool fRightMouseDown;
		TS::ShapeInstance::Thread* thread;

		char szShape[256];
		char szShapeBase[256];

		bool m_male;
		bool m_loadedShapeMale;
		int m_curArmor;

		float rMinDist;
		EulerF rShift;
		float rDefDist;
		float rMaxDist;

		DWORD m_lastUpdated;

		Point2I last;
		Point3F center;

		TS::PointArray points;
		TS::RenderContext context;

	public:
		SkinView();
		~SkinView();
		void setupViewport();
		bool onAdd();
		void onRemove();
		void setSkin(const char* lpszSkin, bool fMale);
		void cycleArmor();
		void setShape();
		Int32 getMouseCursorTag();
		void resize(const Point2I& newPos, const Point2I& newExt);
		void onMouseDown(const SimGui::Event& event);
		void onMouseUp(const SimGui::Event& event);
		void onRightMouseDown(const SimGui::Event& event);
		void onRightMouseUp(const SimGui::Event& event);
		void onRightMouseDragged(const SimGui::Event& event);
		void onMouseDragged(const SimGui::Event& event);
		bool becomeFirstResponder();
		void onPreRender();
		void onRender(GFXSurface* sfc, Point2I offset, const Box2I&);

		DECLARE_PERSISTENT(SkinView);

		Error read(StreamIO& sio, int iVer, int iUsr);
		Error write(StreamIO& sio, int iVer, int iUsr);

		float getFarPlane();
	};

	extern bool gbConsoleFunctionAdded;
}
