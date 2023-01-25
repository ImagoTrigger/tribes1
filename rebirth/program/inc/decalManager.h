#pragma once

#include "SimContainer.h"
#include "ShapeBase.h"
#include "FearDcl.h"
#include "fxRenderImage.h"

class DecalManager : public GameBase
{
	typedef GameBase Parent;

	// TODO: Real value
	static const size_t MAX_DECALS = 200;

public:
	// TODO
	enum DECALTYPE
	{
		//TYPE_FOOTPRINT_LIGHT_LEFT,
		//TYPE_FOOTPRINT_LIGHT_RIGHT,
		//TYPE_FOOTPRINT_MEDIUM_LEFT,
		//TYPE_FOOTPRINT_MEDIUM_RIGHT,
		//TYPE_FOOTPRINT_HEAVY_LEFT,
		//TYPE_FOOTPRINT_HEAVY_RIGHT,
		TYPE_HOLE_BASIC = 6,
		NUM_TYPES
	};

public: //private:

	struct Decal
	{
		int iType;
		Point3F center;
		Point3F worldPts[4];

	};

	class DecalRenderImage : public SimRenderImage
	{
		virtual void setSortValue(TSCamera*);

	protected:
		void render(TSRenderContext& rc) override;

	public:
		int iNumDecals;
		int iCurDecal;

		Decal* rgDecals[MAX_DECALS];
		Resource<GFXBitmap> rgrsDecals[MAX_DECALS];
	};



	virtual void addDecal(const Vector3F& pos, const Vector3F& normal, const Vector3F& perp1, const Vector3F& perp2, DECALTYPE type);
	virtual bool onSimRenderQueryImage(SimRenderQueryImage* query);

public:
	struct DecalInfo
	{
		const char* lpszDecal;
		RealF rSize;
	};
	virtual void reset();
	virtual void addBulletHole(Vector3F position, Vector3F normal, DECALTYPE type);

protected:
	bool onAdd() override;
	void onRemove() override
	{
		// TODO: Figure out why this is needed.
		SimMovement::onRemove();
	}
	bool processQuery(SimQuery* query) override;

public: //private:



	bool fLoaded;
	DecalRenderImage image;



public:
	static int iPrefNumDecals;

	DecalManager();
	virtual ~DecalManager();

	virtual void addFootprint(TMat3F tmat, DECALTYPE type, float rFootspan);
};
