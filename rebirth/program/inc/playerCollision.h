#pragma once

#include "shapeCollision.h"

class PlayerCollisionImage : public ShapeCollisionImage
{
	typedef SimCollisionImage Parent;

	enum
	{
		// TODO: ApplicationType? ApplicationType + 1?
		PlayerCollisionImageType = ApplicationType
	};

	bool checkPlayer(PlayerCollisionImage* image, CollisionSurfaceList* list);

protected:
	bool collide(SimCollisionImage* image, CollisionSurfaceList* list) override;
	void buildImageTransform(SimCollisionImage* image, CollisionSurfaceList* list, TMat3F* mat) override;
	bool checkBox(SimCollisionBoxImage* bi, TMat3F* trans, CollisionSurfaceList* list) override;
	bool checkTerrain(SimCollisionTerrImage* image, CollisionSurfaceList* list) override;
	bool checkInterior(SimCollisionItrImage* image, CollisionSurfaceList* list) override;
	bool checkShape(ShapeCollisionImage* image, CollisionSurfaceList* list) override;

public:
	PlayerCollisionImage();

	Box3F crouchBox;
};
