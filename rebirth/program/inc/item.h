#pragma once

#include "staticbase.h"
#include "SimLightGrp.h"
#include "shapeCollision.h"

class Item : public StaticBase
{
	typedef StaticBase Parent;

	DECLARE_PERSISTENT(Item);

public:
	struct ItemData : public StaticBaseData
	{
	private:
		typedef ShapeBaseData Parent;

	public:

		int imageId;
		int price;
		float mass;
		float drag;
		float density;
		float friction;
		float elasticity;
		int lightType;
		float lightRadius;
		float lightTime;
		Point3F lightColor;
		StringTableEntry typeString;
		const char* hudIcon;
		bool showInventory;
		bool showWeaponBar;
		bool hiliteOnActive;

		Resource<GFXBitmap> hudLROnBitmap;
		Resource<GFXBitmap> hudLROffBitmap;

		Resource<GFXBitmap> hudIOnBitmap;
		Resource<GFXBitmap> hudIOffBitmap;

		ItemData();
		void pack(BitStream* stream) override;
		void unpack(BitStream* stream) override;
		bool preload(ResourceManager * rm, bool server, char errorBuffer[256]) override;
	};

public: //private:
	// TODO Order maybe mirror with Player::ItemImageData
	enum LightType
	{
		NoLight,
		ConstantLight,
		PulsingLight
	};

	// TODO: Real values
	enum
	{
		Visible = BIT(1),
		Pop = BIT(2),
		PopItem = BIT(3)
	};

	// TODO: Value check, also does this belong here or ShapeBase?
	enum
	{
		VelocityMask = BIT(30)
	};

	BitSet32 itemFlags;

	GameBase* throwSource;
	int count;
	TSLight* light;
	bool lastRest;
	DWORD updatePosTime;
	SimTime dropTime;

	int throwerClientId;
	int throwerClientLoginId;





	void throwObject(GameBase* object, float speed, bool careless);
	void updateBlackout();
	bool onSimLightQuery(SimLightQuery * query);
	TSLight* getLight();


	void pop();


protected:
	ItemData* data;
	//ShapeCollisionImage collisionImage;
	bool isRotate;
	bool isCollideable;

	Int32 getDamageId();
	int getDatGroup() override;
	bool processArguments(int argc, const char** argv) override;
	bool onAdd() override;
	void onRemove() override;
	void onDeleteNotify(SimObject* object) override;
	bool initResources(GameBaseData* dat) override;
	void serverProcess(DWORD ct) override;
	void clientProcess(DWORD curTime) override;

	void onCollisionNotify(GameBase* object) override;
	void onDisplacement(SimMovement* displacer, const Point3F& delta) override;
	bool processCollision(SimMovementInfo* info) override;
	bool processQuery(SimQuery* query) override;
	DWORD packUpdate(Net::GhostManager* gm, DWORD mask, BitStream* stream) override;
	void unpackUpdate(Net::GhostManager* gm, BitStream* stream) override;
	Error read(StreamIO& sio, int, int) override;
	Error write(StreamIO& sio, int, int) override;
	bool onSimRenderQueryImage(SimRenderQueryImage* query);

public:
	Item();
	virtual ~Item();

	static void initPersistFields();

	bool hideItem(bool hide);

	virtual bool isRotating() const
	{
		return this->isRotate;
	}

	virtual bool isVisible() const
	{
		return itemFlags.test(Visible);
	}

	virtual bool isPop() const
	{
		return itemFlags.test(PopItem);
	}

	virtual bool hasHulk() const
	{
		// TODO: Wat
		return false;
	}

	virtual int getCount() const
	{
		return this->count;
	}

};
