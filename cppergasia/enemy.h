#pragma once
#include "enemyprojectile.h"
#include "ship.h"
#include "config.h"
#include "player.h"
#include "util.h"

class Enemy : public Ship
{
	float pos_x;
	float pos_y = -200;
	float position;
	unsigned short spawnTexture = 1;
	bool alive = false;
	Player* player = nullptr;
	void fire() override;
	unsigned short hitPoints = 3;
public:
	void update() override;
	void draw() override;
	void init() override;
	bool isAlive() { return alive; }
	float getPosition() { return position; }
	Hitbox getHitbox() override;
	void setHit() { --hitPoints; }
	Enemy(float, float, Player* p);// position
	~Enemy();
};