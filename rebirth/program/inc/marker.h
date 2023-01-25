#pragma once

#include "GameBase.h"
#include "shapeCollision.h"

class Marker : public GameBase
{
	typedef GameBase Parent;

	DECLARE_PERSISTENT(Marker);

public:
	struct MarkerData : public GameBaseData
	{
	private:
		typedef GameBaseData Parent;

	public:

		const char* fileName;

		MarkerData();
		void pack(BitStream* stream);
		void unpack(BitStream* stream);
	};

public: //private:

	Resource<TSShape> shape;

	class MarkerRenderImage : public SimRenderDefaultImage
	{

	} image;

	ShapeCollisionImage collisionImage;

	enum
	{
		PositionMask = LastMaskBit << 1,
		RotationMask = LastMaskBit << 2,
	};

	bool initResources(GameBaseData* data);
	bool loadShape();
	int getDatGroup();
	void setTeam(int team);
	void setPos(const Point3F& pos, const Point3F& rot);
	bool processEvent(const SimEvent* event);
	bool onSimEditEvent(const SimEditEvent* event);
	bool onSimObjectTransformEvent(const SimObjectTransformEvent* event);
	bool processQuery(SimQuery* query);
	bool onSimObjectTransformQuery(SimObjectTransformQuery* query);
	bool onSimCollisionImageQuery(SimCollisionImageQuery* query);
	bool onSimRenderQueryImage(SimRenderQueryImage* query);

	DWORD packUpdate(Net::GhostManager* gm, DWORD mask, BitStream* stream);
	void unpackUpdate(Net::GhostManager* gm, BitStream* stream);
	void inspectRead(Inspect* insp);
	void inspectWrite(Inspect* insp);

public:
	Marker();
	virtual ~Marker();

	static void initPersistFields();
};
