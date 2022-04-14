#pragma once
#include "gameobject.h"
#include "config.h"

class Star : public GameObject
{
	float speed;
	float pos_x;
	float pos_y = -100;
	float size;
	bool outsideCanvas = false;
public:
	void update() override;
	void draw() override;
	void init() override;
	bool isOutsideCanvas() { return outsideCanvas; }
	Star();
	~Star();
};