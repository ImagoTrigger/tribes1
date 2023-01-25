#pragma once

#include "fxRenderImage.h"

class SwooshTrail : public fxRenderImage
{
	struct PointBar
	{
		Point3F centerPoint;
		Point3F unitLeft;
		Point3F leftPoint;
		Point3F rightPoint;
	};

public:
	SwooshTrail(const float in_totalLength, const UInt32 in_numSections, const float in_initialTrailWidth);
	~SwooshTrail();
	void updateTransform(const TMat3F& in_newTransform, const float);
	void setSortValue(TSCamera* io_pCamera);
	bool getBoundingBox(Box3F&);
	void render(TS::RenderContext& io_rRC);
	float m_totalLength;
	UInt32 m_numSections;
	float m_lengthTrigger;
	float m_initialWidth;
	int m_numActiveSections;
	bool m_rendering;
	PointBar* m_pointChain;
};

class SimpleSwooshTrail : public fxRenderImage
{

public:
	SimpleSwooshTrail(const float in_length, const float in_trailWidth);
	void setResources(Resource<GFXBitmap>& rBitmap);
	void loadResources(const char* in_pTextureName, SimManager* io_pManager);
	~SimpleSwooshTrail();
	void render(TS::RenderContext& io_rRC);
	void updateTransform(const TMat3F& in_newTransform, const float in_newTime);
	void setSortValue(TSCamera* io_pCamera);
	bool getBoundingBox(Box3F&);
	bool m_set;
	Resource<GFXBitmap> m_hBitmap;
	SimTime m_lastTime;
	Point3F m_rearPoint;
	Point3F m_unitLeft;
	Point3F m_centerPoint;
	float m_totalLength;
	float m_initialWidth;
	bool m_rendering;
};


