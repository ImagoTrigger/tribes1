#pragma once

#include "m_point.h"
#include "fxRenderImage.h"

class Snowfall : public SimContainer
{
	typedef SimContainer Parent;

	DECLARE_PERSISTENT(Snowfall);

	struct Image sealed : public fxRenderImage
	{
		SFX_HANDLE sound;
		GFXBitmap* bitmap;
		SimManager* manager;
		ImageType imageType;
		Point3F point[4];

		void init();
		void render(TSRenderContext& rc);
		void renderRain(TSRenderContext& rc);
		void renderSnow(TSRenderContext& rc);
	} image;

	bool rain;
	int suspendRendering;
	float intensity;
	float intensityLimit;
	float atenuation;
	float atenGoal;

	Point3F wind;

	

	// TODO: values
	enum
	{
		updateIntensity = 1 << 0,
		updateWind = 1 << 1,
		updateRendering = 1 << 2,
		LastNetFlag = 1 << 3
	};
	
	void init();
	void setNearDist(float value);
	void setIntensity(float value);
	void setWind(const Point2F& direction);
	void setRendering(bool v);
	void setImageType(SimRenderImage::ImageType type);
	void resetColor();

protected:

	bool onAdd() override;
	void onRemove() override;
	bool processQuery(SimQuery* query) override;
	void inspectWrite(Inspect* inspector) override;
	void inspectRead(Inspect* inspector) override;
	bool processArguments(int argc, const char** argv) override;
	
	Error read(StreamIO& s, int a, int b);
	Error write(StreamIO& s, int a, int b);
	DWORD packUpdate(Net::GhostManager*, DWORD mask, BitStream* stream);
	void unpackUpdate(Net::GhostManager*, BitStream* stream);

public:
	static bool precipitation;
	Snowfall();
	
	static void initPersistFields();

};
