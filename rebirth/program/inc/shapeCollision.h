#pragma once

#include "simCollisionImages.h"

class ShapeCollisionImage : public SimCollisionTS3Image
{
protected:
	// TODO: Enum values
	enum
	{
		SphereCollisionImageType = Sphere,
		ShapeCollisionImageType = TSShape
	};

	bool collide(SimCollisionImage* image, CollisionSurfaceList* list) override;
	bool checkBox(SimCollisionBoxImage* bi, TMat3F* trans, CollisionSurfaceList* list) override;

	virtual void buildImageTransform(SimCollisionImage* image, CollisionSurfaceList* list, TMat3F* mat);
	virtual bool checkTerrain(SimCollisionTerrImage* image, CollisionSurfaceList* list);
	virtual bool checkInterior(SimCollisionItrImage* image, CollisionSurfaceList* list);
	virtual bool checkShape(ShapeCollisionImage* image, CollisionSurfaceList* list);

public:
	ShapeCollisionImage();

	SphereF sphere;
};
