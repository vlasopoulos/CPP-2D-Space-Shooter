#pragma once
#include "util.h"
class Collidable {
public:
	virtual Hitbox getHitbox() = 0;
};

class GameObject
{
public:
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void init() = 0;
};