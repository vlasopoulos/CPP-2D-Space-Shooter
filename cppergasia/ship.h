#pragma once
#include "gameobject.h"
#include "projectile.h"
#include <vector>

class Ship : public GameObject, public Collidable
{
protected:
	float lastFiredTime = 0.0f;
	bool canFire = false;
	std::vector<Projectile*> projectiles;
	virtual void fire() = 0;
public:
	void update() = 0;
	void draw() = 0;
	void init() = 0;
	std::vector<Projectile*> getProjectiles() { return projectiles; }
};