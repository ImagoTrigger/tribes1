#pragma once

#define AZ_REGION_SIZE   30
#define AZ_REGION_STRIDE (360/AZ_REGION_SIZE)
#define INC_REGION_SIZE  30
// the region at the very end is for stars below the equator
#define REGION_COUNT     (AZ_REGION_STRIDE*(90/INC_REGION_SIZE))

#include "ShapeBase.h"

class StarField : public SimContainer, public ShapeBase::RenderImage
{
	typedef SimContainer Parent;

	DECLARE_PERSISTENT(StarField);

	struct Star
	{
		Point3F pos;
		UInt8 brightness;
		Star(const Point3F &p, const UInt8 b) : pos(p), brightness(b)
		{
		}
	};
	struct Region
	{
		Bool visible;
		Vector<Star> stars;
	};
	struct RegionPoint
	{
		int regions[4];
		Point3F pos;
	};

	enum
	{
		MAX_STARS = 1500
	};

	bool globeLines;
	bool initialized;
	bool inFrontOfSky;
	bool visible;
	ColorF colors[3];
	bool bottomVisible;

	float m_currentDistance;

	int paletteColors[3];
	Region regions[REGION_COUNT + 1];
	RegionPoint controlPoints[REGION_COUNT + 1];

	enum
	{
		Modified = 1 << 0,
		LastMaskBits = 1 << 1
	};

	

	void toggleGlobeLines();
	void setSortValue();
	
	void setBottomVisible(bool _visible);
	void setVisibility(bool _visible);
	void init(GFXPalette* palette);
	bool setCurrentDistance();

protected:
	void inspectWrite(Inspect* inspect) override;
	void inspectRead(Inspect* inspect) override;
	bool onAdd() override;
	bool processQuery(SimQuery* query) override;
	DWORD packUpdate(Net::GhostManager*, DWORD, BitStream* stream) override;
	void unpackUpdate(Net::GhostManager*, BitStream* stream) override;
	Error read(StreamIO& sio, int version, int u) override;
	Error write(StreamIO& sio, int version, int u) override;
	int version() override;
	void render(TSRenderContext& rc) override;

public:
	static float PrefStars;

	StarField();

	static void initPersistFields();
};
