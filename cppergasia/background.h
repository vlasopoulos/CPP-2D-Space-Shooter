#pragma once
#include "star.h"
#include <vector>

class Background
{
	std::vector<Star*> stars;
public:
	void update();
	void draw();
	void init();
};