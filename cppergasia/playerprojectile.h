#pragma once
#include "projectile.h"

class PlayerProjectile : public Projectile
{
	unsigned int projectileFrame = 0;
public:
	void update() override;
	void draw() override;
	void init() override;
	PlayerProjectile(float origin_x, float origin_y);
	Hitbox getHitbox() override;
};