#include "enemy.h"
#include "graphics.h"
#include "config.h"
#include <random>

void Enemy::fire()
{
	projectiles.push_back(new EnemyProjectile(pos_x, pos_y-10, player->getPlayerPos_x(), player->getPlayerPos_y()));
	graphics::playSound(std::string(ASSET_PATH) + "enemyprojectile.wav",0.7f);
}

void Enemy::update()
{
	if (pos_y < 100)
		++pos_y;
	
	if (hitPoints == 0) {
		alive = false;
	}

	if (canFire) 
	{
		lastFiredTime = graphics::getGlobalTime();
		fire();
		canFire = false;
	}
	else
	{
		// if current_time - captured_time > reload time
		if (graphics::getGlobalTime() - lastFiredTime > 2500 && pos_y == 100)
			canFire = true;
	}

	auto ep = begin(projectiles);
	while (ep != end(projectiles))
	{
		if (!(*ep)->isAlive())
		{
			delete* ep;
			ep = projectiles.erase(ep);
		}
		//else if ((*ep)-> //projectile hitbox xtipaei hitbox player) { ep->setDead; explosion, player->setHit}
		else
		{
			(*ep)->update();
			++ep;
		}
	}
}

void Enemy::draw()
{
	graphics::Brush br;
	br.outline_opacity = 0.0f;

	// draw enemy
	br.texture = std::string(ASSET_PATH) + "enemy_" + std::to_string(spawnTexture) + ".png";
	graphics::drawRect(pos_x, pos_y, 100, 100, br);

	for (auto ep : projectiles)
		if (ep)
			ep->draw();
}

void Enemy::init()
{
	spawnTexture = (rand() % 15) + 1;
	alive = true;
}

Hitbox Enemy::getHitbox()
{
	Hitbox hb;
	hb.cx = pos_x;
	hb.cy = pos_y;
	hb.radius = 35.0f;
	return hb;
}

Enemy::Enemy(float pos, float max_pos, Player * p)
{
	player = p;
	position = pos;
	pos_x = CANVAS_WIDTH / (max_pos+1) * pos + CANVAS_WIDTH / (max_pos + 1);
	init();
}

Enemy::~Enemy()
{
	for (auto ep : projectiles)
	{
		if (ep)
			delete ep;
	}
}
