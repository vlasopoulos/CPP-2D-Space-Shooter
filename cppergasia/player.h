#pragma once
#include "ship.h"
#include "playerprojectile.h"
#include "config.h"
#include "util.h"

class Player : public Ship
{
	float speed = 5.0f;
	float pos_x = CANVAS_WIDTH / 2, pos_y = CANVAS_HEIGHT - CANVAS_HEIGHT / 6;
	unsigned int flameFrame = 0;
	unsigned short hitPoints = 3;
	bool alive = false;
	void fire() override;	
	bool winAnimation = false;
	bool godMode = false;
public:
	void update() override;
	void draw() override;
	void init() override;
	Player();
	~Player();
	float getPlayerPos_x() const { return pos_x; }
	float getPlayerPos_y() const { return pos_y; }
	Hitbox getHitbox() override;
	void setHit() { --hitPoints; }
	unsigned short getHitpoints() { return hitPoints; }
	bool isAlive() { return alive; }
	void playWinAnimation() { winAnimation = true; }
	void enterGodMode() { godMode = true; }
};