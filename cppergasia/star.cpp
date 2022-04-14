#include "star.h"
#include "graphics.h"
#include <random>

void Star::update()
{
	pos_y += speed * graphics::getDeltaTime() / 10.0f;
	if (pos_y > CANVAS_HEIGHT + size)
		outsideCanvas = true;
}

void Star::draw()
{
	graphics::Brush br;
	br.outline_opacity = 0.0f;
	br.fill_secondary_opacity = 1.0f;
	br.gradient = true;
	graphics::drawDisk(pos_x, pos_y, size / 2.0f, br);
}

void Star::init()
{
	speed = 5.0f + float(rand()) / RAND_MAX * 10.0f;
	pos_x = float(rand()) / RAND_MAX * CANVAS_WIDTH;
	size = 1.0f + float(rand()) / RAND_MAX * 4.0f;
}

Star::Star()
{
	init();
}

Star::~Star()
{
}
