#pragma once

#include "SimContainer.h"
#include "Console.h"
#include "Sim3DEv.h"
#include "SimGuiTSCtrl.h"
#include "SimResource.h"
#include "SimGame.h"
#include "g_bitmap.h"
#include "g_surfac.h"
#include "ShapeBase.h"
#include "SimSetIterator.h"

class FearMissionEditor : public SimContainer
{
	// TODO: Guess SimContainer
	typedef SimContainer Parent;

public:
	class SelectionSet : public SimSet
	{
		typedef SimSet Parent;
	public:
		Point3F mCentroid;

		void deleteSet();
		void clearSet();
		SimObject* addObject(SimObject* obj);
		void removeObject(SimObject* obj);
		
		bool anyItemLocked();
		bool objectInSet(const SimObject* obj);
	
		void calcCentroid();
		virtual Point3F getCentroid() const
		{
			return this->mCentroid;
		}
	};

	struct TypeInfo
	{
		char* mClassName;
		DWORD mPlaceMask;
		Resource<GFXBitmap> mSelectedBmp;
		Resource<GFXBitmap> mUnselectedBmp;
		TypeInfo();
		virtual ~TypeInfo();
	};

	// TODO ORder
	enum
	{
		ArrowCursor,
		HandCursor,
		GrabHand,
		MoveCursor,
		RotateCursor,
		LockCursor
	};

	struct CursorInfo
	{
		int mCursorId;
		Resource<GFXBitmap> mBmp;
		Point2I mHotspot;
	};

	Vector<CursorInfo*> mCursors;
	int mDropType;
	Point3F mPlaneXYIntercept;
	float mPlaneZIntercept;
	Point2I mLastMousePos;
	SimCollisionInfo mGrabInfo	;
	DWORD mGrabMask;
	float mRotationSnap;
	int mRotateAxis;
	Point3F mGranularity;
	DWORD mLastTime;
	EulerF mRotSum;
	SimCollisionInfo mPlaceInfo;
	Point3F mPlaneXYOffset;
	float mPlaneZOffset;

	struct InfoEntry
	{
		TMat3F mTmat;
		int mNum;
		SimObjectId mId;
		SimManager* mManager;
	};
	SelectionSet mSelection;
	Vector<InfoEntry> mUndoInfo;

	SimGui::Canvas* getCanvas() const
	{
		return this->mCanvas;
	}

	struct RenderImage : public ShapeBase::RenderImage
	{
		void render(TSRenderContext& rc);
		SimManager* mManager;
		FearMissionEditor* mME;
	} mRenderImage;

	int getWorldId(SimObject* obj);
	DWORD getPlaceMask(const SimObject* obj);
	TypeInfo* getTypeInfo(const SimObject* obj);
	TypeInfo* getTypeInfo(const char* name);
	bool removeTypeInfo(const char* name);
	bool addTypeInfo(const char* name, int mask, const char* selBmpName, const char* unselBmpName);
	FearMissionEditor();
	~FearMissionEditor();
	bool init();
	void lockManager();
	void unlockManager();
	void onDeleteNotify(SimObject* obj);
	bool onAdd();
	SimGroup* getAddGroup();
	SimObject* addObject(SimObject* obj);
	void onRemove();
	bool processQuery(SimQuery* query);
	bool onSimInputPriorityQuery(SimInputPriorityQuery* query);
	bool onSimRenderQueryImage(SimRenderQueryImage* query);
	bool processEvent(const SimEvent* event);
	SimObject* getCamera();
	bool getTransform(SimObject* obj, TMat3F& transform);
	bool setTransform(SimObject* obj, TMat3F& transform);
	// TODO: false?
	void moveObjectRelative(SimObject* obj, Point3F& delta, bool allowRecurse = false);
	// TODO: false?
	void moveObjectAbsolute(SimObject* obj, Point3F& pos, bool allowRecurse = false);
	// TODO: false?
	void dropObjectDown(SimObject* obj, bool allowRecurse = false);
	bool getDropTarget(int dropType, Point3F& target);
	// TODO: false?
	void onDrop(SimObject* obj, int dropType, bool allowRecurse = false);
	// TODO: false?
	void rotateObject(SimObject* obj, Point3F& anchor, EulerF& rot, bool allowRecurse = false);
	void getSystemKeys();
	bool getPlaneIntercepts(const Sim3DMouseEvent* event);
	bool onSim3DMouseEvent(const Sim3DMouseEvent* event);
	bool onSimEditEvent(const SimEditEvent* event);
	bool onSimGainFocusEvent(const SimGainFocusEvent* event);
	bool onSimLoseFocusEvent(const SimLoseFocusEvent* event);
	// TODO: Def -1
	bool getLOSIntercept(const Sim3DMouseEvent* event, SimCollisionInfo* info, DWORD allowedTypes, int objId = -1);
	SimObject* getObject(UINT objID);
	void getConsoleOptions();
	void copySelection();
	void dropSelection();
	// TODO: default false?
	void pasteFile(const char* pasteFile, bool toCopyPosition = false);
	void pasteSelection();
	void deleteSelection();
	void placeBookmark(int index);
	void gotoBookmark(int index);
	// TODO: Def false
	void saveInfo(SimObject* obj, bool allowRecurse = false);
	void restoreInfo();
	void loadCursor(const int cursorId, const char* name, Point2I& hotspot);
	void setCursor(const int cursorId);
	void loadBitmap(Resource<GFXBitmap>& hBitmap, const char* name);

	void rebuildCommandMap();
	int mDefPlaceMask;
	Vector<TypeInfo*> mTypeInfo;
	Resource<GFXBitmap> mDefSelectedBmp;
	Resource<GFXBitmap> mDefUnselectedBmp;

	// TODO Order
	enum
	{
		DropAtCamera,
		DropWithRotAtCamera,
		DropBelowCamera,
		DropToScreenCenter,
		DropToSelectedObject,
		DropToCopyPosition
	};

	// TODO Order
	enum
	{
		InputFocus = BIT(0),
		RenderHandles = BIT(1),
		ConstrainXAxis = BIT(2),
		ConstrainYAxis = BIT(3),
		ConstrainZAxis = BIT(4),
		Mod1 = BIT(5),
		Mod2 = BIT(6),
		Mod3 = BIT(7),
		SnapToGrid = BIT(7),
		ShowEditObjects = BIT(8),
		RotateXAxis = BIT(9),
		RotateYAxis = BIT(10),
		RotateZAxis = BIT(11),
		UsePlaneMovement = BIT(12),
		DropToGround = BIT(13),
		SnapRotations = BIT(14),
		LeftMouseDrag = BIT(15)
	};

	BitSet32 mFlags;
	SimManager* mTargetManager;
	SimGui::Canvas* mCanvas;
	Point3F copyPosition;;
	TMat3F mBookmarkPos[10];
	Resource<GFXBitmap> mLockSelectedBmp;
	Resource<GFXBitmap> mLockUnselectedBmp;

public:
	void setManager(SimManager* value)
	{
		this->mTargetManager = value;
	}
	void setCanvas(SimGui::Canvas* value)
	{
		this->mCanvas = value;
	}
	void setGrabMask(const int value)
	{
		this->mGrabMask = value;
	}
	void setDefPlaceMask(const int value)
	{
		this->mDefPlaceMask = value;
	}
};
