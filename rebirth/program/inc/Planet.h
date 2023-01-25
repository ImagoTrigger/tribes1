#pragma once

#include "SimNetObject.h"
#include "gameBase.h"
#include "fxRenderImage.h"

class Planet : public SimNetObject
{
	typedef SimNetObject Parent;

	DECLARE_PERSISTENT(Planet);

public:
	class LensFlare;

private:
	class PlanetRenderImage sealed : public fxRenderImage
	{
		typedef FearRenderImage Parent;

	protected:
		void render(TSRenderContext& rc) override;

		//void updateSunOverride(const bool in_attenuate, const float in_factor, const ColorF& in_color) override
		//{
		//	throw std::exception("Shouldn't ever get here.");
		//}

	public:
		LensFlare* lensFlare;
		float size;
		float distance;
		Point3F position;
		GFXBitmap* texture;
		float visibleDistance;

	} planet;

public:
	class LensFlare sealed : public fxRenderImage
	{
		typedef FearRenderImage Parent;

		friend class PlanetRenderImage;

		struct FlareInfo
		{
			int textureIndex;
			float scaleRange;
			float minScale;
			float dist;
			bool rotate;
			
			FlareInfo(const int textureIndex, const float scaleRange, const float minScale, const float dist, const bool rotate):
				textureIndex(textureIndex),
				scaleRange(scaleRange),
				minScale(minScale),
				dist(dist),
				rotate(rotate)
			{				
			}
		};
		
		static const char* filename;
		static bool renderDetail;
		SimContainer* root;
		Resource<TSMaterialList> hMaterialList;
		bool initialized;
		bool visible;
		Point3F sunPosProjected;
		Point3F sunPosWorld;
		int renderCount;
		bool obscured;
		SimObjectId excludedId;

		Vector<FlareInfo> flares;
		bool overrideWashout;
		ColorF color;
		
		void setSunPos(bool vis, const Point3F& sunP, const Point3F& worldPos);
		
	protected:
		void render(TSRenderContext& rc) override;

		//void updateSunOverride(const bool in_attenuate, const float in_factor, const ColorF& in_color) override
		//{
		//	throw std::exception("Shouldn't ever get here.");
		//}

	public:
		LensFlare();

		void setColor(const ColorF& color)
		{
			this->color = color;
		}

		void setRootContainer(SimContainer* simContainer)
		{
			this->root = simContainer;
		}

		bool isInitialized() const
		{
			return this->initialized;
		}

		void initialize(SimManager* manager);
	};

public: //private:
	LensFlare lensFlare;

	enum NetMaskBits
	{
		Modified = 1,
	};

	float azimuth;
	float incidence;
	bool castShadows;
	bool useLensFlare;
	bool inLightSet;
	bool inRenderSet;
	bool loaded;

	ColorF intensity;
	ColorF ambient;



	StringTableEntry fileName;

	Resource<GFXBitmap> hTexture;
	TSLight light;

	


	

	virtual void set(const char*, float _azimuth, float _incidence, bool _castShadows, bool _useLensFlare, ColorF _intensity, ColorF _ambient);
	virtual void load();
	virtual void unload();

	virtual void streamWrite(StreamIO& sio);
	virtual void streamRead(StreamIO& sio);

protected:

	void inspectWrite(Inspect* inspect) override;
	void inspectRead(Inspect* inspect) override;
	bool processArguments(int argc, const char** argv) override;
	bool processQuery(SimQuery* query) override;
	bool onAdd() override;
	void onRemove() override;
	DWORD packUpdate(Net::GhostManager*, DWORD, BitStream* stream) override;
	void unpackUpdate(Net::GhostManager*, BitStream* stream) override;

public:
	static bool shadows;
	static Point3F shadowDirection;

	Planet();
	virtual ~Planet();

	static void initPersistFields();
};
