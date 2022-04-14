#include "playerprojectile.h"
#include "graphics.h"

void PlayerProjectile::update()
{
	pos_y -= speed * graphics::getDeltaTime() / 10.0f;
	if (pos_y < 0 - size)
		alive = false;
}

void PlayerProjectile::draw()
{
	graphics::Brush br;
	br.outline_opacity = 0.0f;
	br.texture = std::string(ASSET_PATH) + "playerprojectile\\" + std::to_string(projectileFrame++ % 30 + 1) + ".png";
	graphics::setOrientation(90);
	graphics::drawRect(pos_x, pos_y, size, size, br);
	graphics::resetPose();
}

void PlayerProjectile::init()
{
	size = 30.0f;
	speed = 10.0f;
	alive = true;
}

PlayerProjectile::PlayerProjectile(float origin_x, float origin_y)
{
	pos_x = origin_x;
	pos_y = origin_y;
	init();
}

Hitbox PlayerProjectile::getHitbox()
{
	Hitbox hb;
	hb.cx = pos_x;
	hb.cy = pos_y;
	hb.radius = 5.0f;
	return hb;
}
