//--------------------------------------------------------------------------- 
//
// simSky.h
//
//--------------------------------------------------------------------------- 

#pragma once

#include "simNetObject.h"
#include "simRenderGrp.h"
#include "ts_shapeInst.h"
#include "move.h"
#include "inspect.h"
#include "simContainer.h"
#include "SimPreloadManager.h"

// by default the stars are in front of the sky c
#define PLANET_DISTANCE           19000.0f
#define TEXTUREDSKY_DISTANCE      20000.0f
#define STARFIELD_FRONT_DISTANCE  19500.0f
#define STARFIELD_BACK_DISTANCE   21500.0f

extern float STARFIELD_DISTANCE;

#define BACKGROUND_SORTVALUE       0.0f
#define TEXTUREDSKY_SORTVALUE      10.0f
#define STARFIELD_FRONT_SORTVALUE  20.0f
#define PLANET_SORTVALUE           30.0f
#define STARFIELD_BACK_SORTVALUE   40.0f

//--------------------------------------------------------------------------- 


#define TEXTUREDSKY_HEIGHT 600.0f

class Sky : public SimContainer, SimRenderImage
{
public: //private:
	typedef SimContainer Parent;

protected:
	enum Constants {
		// 
		CurrentFileVersion = 2,
	};

	bool resolveColor;
	int skyIndex;
	int hazeIndex;
	ColorF skyColor;
	ColorF hazeColor;
	int paletteKey;

	enum NetMaskBits
	{
		Modified = 1,
	};

	bool    loaded;
	int     matListTag;
	int     bottomColor;
	int     textures[16];
	float   featurePosition;
	
	StringTableEntry dmlName;	
	Resource<TSMaterialList> hMaterialList;
	float size;
	float distance;
	bool isInitialized;

	//void streamRead(StreamIO &sio);
	//void streamWrite(StreamIO &sio);

	void load();
	void unload();
	void calcPoints();
	bool initialize();
	void makeBoundingBox();
	void setFillColor(GFXSurface *surface, int &index, ColorF &color);

	void renderSkyBand(TSRenderContext &rc);
	void renderSolid(TSRenderContext &rc);
	void set(ColorF color);

public:
	static float PrefSkyDetail;
	Sky();
	~Sky();

#pragma warn -hid
	void render(TSRenderContext &rc) override;
#pragma warn +hid

	void set(const char* dmlName, float _featurePosition, int _textures[16]);
	//void setMaterialListTag(int _matListTag);

	bool processQuery(SimQuery*) override;
	bool processArguments(int argc, const char **argv) override;
	bool onAdd() override;
	void onRemove() override;
	//void onPreLoad(SimPreLoadManager *splm) override;
	void inspectRead(Inspect *inspector) override;
	void inspectWrite(Inspect *inspector) override;

	bool processEvent(const SimEvent* event) override;
	bool onSimTimerEvent(const SimTimerEvent*);

	virtual float getDistance();

	DWORD packUpdate(Net::GhostManager *gm, DWORD mask, BitStream *stream) override;
	void unpackUpdate(Net::GhostManager *gm, BitStream *stream) override;

	DECLARE_PERSISTENT(Sky);
	static void initPersistFields();
	//Persistent::Base::Error read(StreamIO &, int version, int user) override;
	//Persistent::Base::Error write(StreamIO &, int version, int user) override;
	int version() override;
};
