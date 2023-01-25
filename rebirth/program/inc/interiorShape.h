#pragma once
#include "BanList.h"
#include "simInterior.h"
#include "ShapeBase.h"
//#include "itrShape.h"
//#include "simInteriorShape.h"
//#include "itrShapeEdit.h"


enum ItrLinkFace : DWORD
{
	ItrFaceNone = 0,

	ItrFaceMinX = 1 << 7,   // These values map to those in the outside bits
	ItrFaceMinY = 1 << 6,   //  field on the geometry...
	ItrFaceMinZ = 1 << 5,
	ItrFaceMaxX = 1 << 4,
	ItrFaceMaxY = 1 << 3,
	ItrFaceMaxZ = 1 << 2,

	ItrFaceAll = 252
};

class LinkVertexArena;
//{
//public:
//	LinkVertexArena();
//	virtual ~LinkVertexArena();
//	void addInterior(InteriorShape* io_pAdd,
//		const ItrLinkFace    in_linkFace);
//	void removeInterior(InteriorShape* io_pRemove);
//};

class InteriorShape : public GameBase
{
	typedef GameBase Parent;

	DECLARE_PERSISTENT(InteriorShape);

	static const float csm_boxContainerWidth;
	static const Int32 csm_fileVersion;
	
	static const float csm_BBoxExtension;



	enum RenderForce
	{
		ForceEdit = 1 << 0,
		ForceLink = 1 << 1
	};

	struct InteriorLink
	{
		InteriorShape* pInterior;
		LinkVertexArena* pVertexArena;
		ItrLinkFace linkFace;

		//bool testFace(const int in_outsideBits) const;
	};

public:
	static UInt32 sm_minLightUpdateMS;

	struct LightAnimParam
	{
		float  time;
		bool   active;
		UInt32 dummy1;
		UInt32 dummy2;
	};

public: //private:

	Vector<ITRInstance::LightThread*> m_lightThreads;
	Vector<LightAnimParam> m_lightAnimParams;
	typedef Vector<InteriorLink> InteriorLinkList;

	class RenderImage : public SimRenderImage
	{
	protected:
		void render(TS::RenderContext& rc) override;

	public:
		bool linkRendering;

		ITRInstance* currShape;	
		ITRRender    rend;
		InteriorShape* pInteriorShape;
		TMat3F transform;
	} m_renderImage;

	InteriorLinkList m_currentLinks;
	SimTag m_scopeTag;
	EulerF m_shapeRotation;
	Point3F m_shapePosition;
	Point3F m_centerPos;
	const char* m_pFileName;

	SimCollisionItrImage m_collisionImage;

	Vector<UInt32> m_checkVals;
	
	// TODO: Values 
	enum
	{
		Uninitialized = -1,
		NotContainer,
		IsContainer
	};
	bool m_isContainer;
	DWORD m_lastUpdatedTime;
	bool m_disableCollisions;

	virtual void remapTeamTextures(int in_team);
	virtual void initRenderImage();
	virtual void setIsContainer(const bool in_isContainer);
	virtual bool missionLitName();
	virtual void getBaseFilename(String& str);
	virtual void setFileName(const char* in_pFileName);
	virtual bool initInteriorResources();
	virtual void shutdownLights();
	virtual void initLightParams();
	virtual void restartLights();
	bool onSimRegisterTextureEvent(const SimRegisterTextureEvent* event);
	bool onSimEditEvent(const SimEditEvent* event);
	// TODO: Default false?
	virtual void set(const TMat3F& in_trans, const bool in_reextractAngles = false);
	virtual void set(const EulerF& in_rot, const Point3F& in_pos);
	bool onSimCollisionImageQuery(SimCollisionImageQuery* query);
	virtual void readInitialPacket(BitStream* stream);
	virtual void writeInitialPacket(BitStream* stream);
	virtual bool scopeLinks(SimContainerScopeContext& sc);
	virtual void unlinkMe(const InteriorShape* in_pLinked);
	virtual bool linkMe(InteriorShape* in_pNewLink, LinkVertexArena* io_pArena);
	virtual void clearLinks();
	virtual void findAllLinks();
	virtual bool renderLinks(SimContainerRenderContext& rc);
	virtual Box3F getITRSpaceBBox(const InteriorShape* io_pOtherItr) const;
	ItrLinkFace getAbuttingFace(const Box3F& in_rMyBox, const Box3F& in_rOtherBox) const;
	virtual int correctOutsideBits(const int in_oldBits, TS::Camera* io_camera, TS::PointArray* io_pointArray);
	
	virtual void writeCheckVals(StreamIO* pStream);
	virtual void readCheckVals(StreamIO* pStream);
	virtual bool verifyCheckVals();
	virtual void buildCheckVals();
	

protected:	
	enum NetMaskFlags
	{
		SimShapeResPt = LastMaskBit,
		PosRotMask = LastMaskBit << 1,//PositionMask | RotationMask
		LightActiveMask = LastMaskBit << 2,
		EditModeMask = LastMaskBit << 3,
		LastMaskBit = LastMaskBit << 4		
	};
	
	void buildContainerBox(const TMat3F& in_rTrans, Box3F* out_pBox) override;
	void setTeam(int in_team) override;
	bool processQuery(SimQuery* query) override;
	bool processEvent(const SimEvent* event) override;
	bool processArguments(int argc, const char** argv) override;
	bool onAdd() override;
	void clientProcess(DWORD in_curTime) override;
	bool onSimObjectTransformEvent(const SimObjectTransformEvent* event);
	bool onSimObjectTransformQuery(SimObjectTransformQuery* query);
	bool onSimRenderQueryImage(SimRenderQueryImage* query);
	void inspectRead(Inspect* inspector) override;
	void inspectWrite(Inspect* inspector) override;
	DWORD packUpdate(Net::GhostManager* gm, DWORD mask, BitStream* stream) override;
	void unpackUpdate(Net::GhostManager* gm, BitStream* stream) override;
	Error read(StreamIO& sio, int ignore_version, int user) override;
	Error write(StreamIO& sio, int ignore_version, int user) override;
	int version() override;
	bool render(SimContainerRenderContext& rc) override;
	bool scope(SimContainerScopeContext& sc) override;

public:
	InteriorShape();
	virtual ~InteriorShape();

	static void initPersistFields();

	bool m_forceRender;
	virtual bool getWeatherDistance(const TMat3F& in_rWorldTrans, float& out_rDistance);
	virtual ITRInstance* getInstance() const
	{
		return this->m_renderImage.currShape;
	}

	virtual bool isMissionLit();
};
