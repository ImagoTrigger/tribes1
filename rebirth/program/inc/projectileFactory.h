#pragma once

class Projectile;

struct ProjectileDataType sealed
{
	int type;
	int dataType;
};

extern Projectile* createProjectile(ProjectileDataType& projectile);
