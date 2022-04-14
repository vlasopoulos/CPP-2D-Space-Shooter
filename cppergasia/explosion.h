#pragma once
#include "gameobject.h"

class Explosion : public GameObject
{
	float pos_x, pos_y;
	unsigned short explosionFrame;
	bool ended = true;
public:
	void update() override;
	void draw() override;
	void init() override;
	Explosion(float, float);
	~Explosion();
	bool hasEnded() { return ended; }
};