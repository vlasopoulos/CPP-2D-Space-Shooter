#pragma once
#include "projectile.h"

class EnemyProjectile : public Projectile
{
	float speed_x, speed_y;
	unsigned int projectileFrame = 0;
public:
	void update() override;
	void draw() override;
	void init() override;
	EnemyProjectile(float or_x, float or_y, float target_x, float target_y);
	Hitbox getHitbox() override;
};