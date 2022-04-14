#pragma once
#include "gameobject.h"
#include "config.h"

class Projectile : public GameObject, public Collidable
{
protected:
	float pos_x, pos_y;
	float theta = 90.0f;
	float speed;
	float size;
	bool alive = false;
public:
	void update() = 0;
	void draw() = 0;
	void init() = 0;
	bool isAlive() { return alive; }
	void setDead() { alive = false; }
};