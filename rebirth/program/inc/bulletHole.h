#pragma once

#include "simEv.h"
#include "SimContainer.h"

class BulletHole : public SimContainer
{	
	// TODO Guess SimContainer?
	typedef SimContainer Parent;

	class BulletHoleRenderImage : public SimRenderImage
	{
		// TODO Guess SimRenderImage?
		typedef SimRenderImage Parent;

		Point3F normal;

		Point3F worldPts[3];

		
		

	public:
		Point3F centerPoint;
		float rTerrainPerspectiveDistance;
		GFXBitmap* pBitmap;

		void buildPoints(const Point3F& in_rCenter, const Point3F& in_rNormal, const UInt8 in_holeIndex);
		void render(TS::RenderContext& rc) override;
		void setSortValue(TSCamera* io_pCamera);
	};

	static float getBulletHoleTimeout()
	{
		return sm_bulletHoleTimeout;
	}

	SimTime m_timeOutTime;
	UInt8 m_bulletHoleIndex;

	Resource<GFXBitmap> m_resBmp;
	BulletHoleRenderImage m_renderImage;
	

	static const char* sm_pBulletHolePrefString;
	static float sm_bulletHoleTimeout;
	static const Point2F sm_pTextureCoords[];

	BulletHole(const Point3F& in_rPoint, const Point3F& in_rNormal, const UInt8 in_bulletHoleIndex);
	bool onAdd() override;
	bool processQuery(SimQuery* query);
	bool processEvent(const SimEvent* event);
	bool onSimRenderQueryImage(SimRenderQueryImage* query);
	bool onSimTimerEvent(const SimTimerEvent*);
};
