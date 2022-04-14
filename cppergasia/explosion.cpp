#include "explosion.h"
#include "graphics.h"
#include "config.h"

void Explosion::update()
{
}

void Explosion::draw()
{
	if (explosionFrame <= 30) {
		graphics::Brush br;
		br.outline_opacity = 0.0f;
		br.texture = std::string(ASSET_PATH) + "explosion\\00" + std::to_string(explosionFrame++) + ".png";
		graphics::drawRect(pos_x, pos_y, 150.0f, 150.0f, br);
	}
	else {
		ended = true;
	}
}

void Explosion::init()
{
	explosionFrame = 1;
	ended = false;
	graphics::playSound(std::string(ASSET_PATH) + "boom.wav", 0.7f);
}

Explosion::Explosion(float x, float y)
{
	pos_x = x;
	pos_y = y;
	init();
}

Explosion::~Explosion()
{
}
