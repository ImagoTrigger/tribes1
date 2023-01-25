#pragma once

#include "SimContainer.h"
#include "simGuiTSCtrl.h"
#include "g_font.h"
#include "SimGuiSimpleText.h"
#include "m_box.h"
#include "m_point.h"

class MissionCenterPos : public SimContainer
{
	// TODO: Guess SimContainer
	typedef SimContainer Parent;

	DECLARE_PERSISTENT(MissionCenterPos);

public:
	Point2F pos;
	Point2F extent;

protected:
	bool onAdd() override;
	bool processArguments(int argc, const char** argv) override;
	void inspectWrite(Inspect* insp) override;
	void inspectRead(Inspect* insp) override;
	Error write(StreamIO& sio, int version, int user) override;
	Error read(StreamIO& sio, int version, int user) override;
	DWORD packUpdate(Net::GhostManager* gm, DWORD mask, BitStream* stream) override;
	void unpackUpdate(Net::GhostManager*, BitStream* stream) override;

public:
	MissionCenterPos();
	static void initPersistFields();

};

#define ALPHAPAL_INDEX 1976
#define MapFilterAll INT_MAX

namespace FearGui
{
	class TSCommander : public SimGui::TSControl
	{
		// TODO: Guess Control parent
		typedef TSControl Parent;

		DECLARE_PERSISTENT(TSCommander);

		static const int MapFilterPlayers = 15;

		struct zoomRect
		{
			Point2I pos;
			Point2I ext;
		};

		static const size_t MaxNumTargs = 256;

		static const size_t BmpCount = 8;

		static const size_t BmpWhereAmI_Count = 8;

		static int prefMapFilter;
		static bool prefShowSensor;
		static bool prefShowNametags;
		static bool prefSensorTranslucent;
		static int mZoomTransitionTime;

		bool execStarredCommand;
		bool draggingMouse;
		bool scrollingMouse;
		bool zoomMode;
		bool centerMode;
		float nearPlane;
		float farPlane;
		RectF worldBounds;
	public:
		// TODO Enum members
		enum
		{
			SelectingMode,
			WaypointMode,
			// ?
			//ZoomingMode 
		};
		int mouseMode;

		// TODO: float? int?
		float playerFacingAngle;
		bool deselectUnits;
		int selectType;

		Point2F worldPosition;
		Point2F worldExtent;
		Point2F worldScale;

		bool mbZooming;
		bool mbPreventDragging;
		int zoomLevel;

		int numTargets;

		GFXBitmap* bitmapList[4][4];

		int curCommand;
		const char* curCommandString;

		PlayerManager* playerManager;
		Resource<GFXFont> textFont;
		Resource<GFXBitmapArray> bma;
		Resource<GFXBitmapArray> playerBMA;

		Resource<GFXBitmap> bmpXMarksTheSpot;

		int startZoomTime;

		Point2I targetZoomPosition;
		Point2I targetZoomExtent;

		Point2I startZoomPosition;
		Point2I startZoomExtent;

		Point2I origPosition;
		Point2I mouseDownPoint;
		Point2I curMousePoint;

		DWORD startCenterTime;
		Point2I startCenterPosition;
		Point2I targetCenterPosition;
		//TSRenderContext renderContext;
		//TS::Camera* camera;
		//TS::Camera* orthographicCamera;
		//ColorF alphaColor;
		//float alphaBlend;

	public:
		struct SensorTargetInfo
		{
			Point2I pos;
			int team;

			int damageStatus;
			bool inUse;
			int activeStatus;
			int datGroup;
			int datId;
			int playerId;
			const char* name;

			bool selected;
		};
		
		SensorTargetInfo targs[MaxNumTargs];

		virtual void resetPos();

		bool inZoomMode() const
		{
			return this->zoomMode;
		}

		bool isFilterOn(const int value) const
		{
			return this->prefMapFilter & value;
		}
	public:		
		static const char* validateZoomTime(CMDConsole *, int id, int argc, const char * argv[]);
		
				
		virtual void drawCommanderIcons(GFXSurface* sfc, Point2I offset, BYTE mode);
		virtual bool setupCamera(const Box2I& visibleBox, const Box2I& boundsBox);
		bool onSimInputEvent(const SimInputEvent* event);
		virtual void setMouseMode(int mode);
		// TODO: Default -1?
		virtual void setCommandWaypoint(const Point2I& cmdPoint, int targIdx = -1);
		virtual void setCommandWaypointItem(int index);
				
		virtual void setSelectedTurret(int index);
		virtual int getSelectedObject();
		virtual int getSelectedPlayer();
		virtual void setSelectedObject(int index);
		virtual void setSelectedPlayer(int id, bool value);
		virtual int getPlayerDamage(int playerID);
		virtual int getPlayerStatus(int playerID);
		virtual int getPlayerTargIndex(int playerID);
		virtual int getTargetDamage(int index);
		virtual int getTargetStatus(int index);
		virtual void selectTarget(int index, bool value);
		virtual void getNewCenterModePos(Point2I& newPos, const Point2I& newExt);
		
		virtual void setCenterMode(Point2I& newPos);
		virtual void centerView();


	public:
		bool onAdd() override;
		void onPreRender() override;
		void onRender(GFXSurface* sfc, Point2I offset, const Box2I& updateRect) override;
		Int32 getMouseCursorTag() override;
		bool processEvent(const SimEvent* event) override;
		void onMouseDown(const SimGui::Event& event) override;
		void onMouseDragged(const SimGui::Event& event) override;
		void onMouseUp(const SimGui::Event& event) override;
		void onRightMouseDown(const SimGui::Event& event) override;
		void onRightMouseDragged(const SimGui::Event& event) override;
		void onRightMouseUp(const SimGui::Event& event) override;
		void parentResized(const Point2I&, const Point2I& newParentExtent) override;

	public:
		TSCommander();
		virtual ~TSCommander();
		virtual int getSelectedTurret();
		virtual void buildMap();
		virtual void issueCommand(int command, const char* message);

		virtual void setZoomMode(bool value)
		{
			this->zoomMode = value;
		}

		virtual void zoomIn();
		virtual void zoomOut();

		virtual void setCenterMode(bool on_off);

		virtual void setSelectType(const int value)
		{
			this->selectType = value;
		}

		virtual void cancelWaypointMode()
		{
			this->mouseMode = SelectingMode;
		}

		virtual bool inWaypointMode() const
		{
			return this->mouseMode == WaypointMode;
		}
	};
}
