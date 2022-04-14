#include "enemyprojectile.h"
#include "graphics.h"
#include "config.h"
#include <cmath>

#define PI 3.14159265

void EnemyProjectile::update()
{
	pos_x += speed_x * graphics::getDeltaTime() / 10.0f;
	pos_y += speed_y * graphics::getDeltaTime() / 10.0f;
	if (pos_x<0 - size || pos_x>CANVAS_WIDTH + size || pos_y > CANVAS_HEIGHT + size)
		alive = false;
}

void EnemyProjectile::draw()
{
	graphics::Brush br;
	br.outline_opacity = 0.0f;
	br.texture = std::string(ASSET_PATH) + "enemyprojectile\\tile0" + std::to_string(projectileFrame++ % 61) + ".png";
	graphics::drawRect(pos_x, pos_y, size, size, br);
	//graphics::drawDisk(currentpos_x, currentpos_y, size , br);
}

void EnemyProjectile::init()
{
	size = 80.0f;
	speed = 6.0f;
	speed_x = cos(theta) * speed;
	speed_y = sin(theta) * speed;
	alive = true;
}

EnemyProjectile::EnemyProjectile(float origin_x, float origin_y, float target_x, float target_y)
{
	pos_x = origin_x;
	pos_y = origin_y;
	theta = atan2(target_y - origin_y, target_x - origin_x) ;
	init();
}

Hitbox EnemyProjectile::getHitbox()
{
	Hitbox hb;
	hb.cx = pos_x;
	hb.cy = pos_y;
	hb.radius = 10.0f;
	return hb;
}
