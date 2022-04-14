#include "player.h"
#include "graphics.h"

void Player::fire()
{
	projectiles.push_back(new PlayerProjectile(pos_x, pos_y - 30.0f));
	graphics::playSound(std::string(ASSET_PATH) + "playerprojectile.wav", 0.2f);
}

void Player::update()
{
	if (!winAnimation)
	{
		if (graphics::getKeyState(graphics::SCANCODE_A) || graphics::getKeyState(graphics::SCANCODE_LEFT))
		{
			pos_x -= speed * graphics::getDeltaTime() / 10.0f;
		}
		if (graphics::getKeyState(graphics::SCANCODE_D) || graphics::getKeyState(graphics::SCANCODE_RIGHT))
		{
			pos_x += speed * graphics::getDeltaTime() / 10.0f;
		}
		if (graphics::getKeyState(graphics::SCANCODE_W) || graphics::getKeyState(graphics::SCANCODE_UP))
		{
			pos_y -= speed * graphics::getDeltaTime() / 10.0f;
		}
		if (graphics::getKeyState(graphics::SCANCODE_S) || graphics::getKeyState(graphics::SCANCODE_DOWN))
		{
			pos_y += speed * graphics::getDeltaTime() / 10.0f;
		}

		if (pos_x < 60) pos_x = 60;
		if (pos_x > CANVAS_WIDTH-60) pos_x = CANVAS_WIDTH-60;
		if (pos_y <60) pos_y = 60;
		if (pos_y > CANVAS_HEIGHT-60) pos_y = CANVAS_HEIGHT-60;

		if (hitPoints <= 0)
			if(!godMode)
				alive = false;

		if (graphics::getKeyState(graphics::SCANCODE_SPACE) && canFire)
		{
			lastFiredTime = graphics::getGlobalTime();
			//fire
			fire();
			canFire = false;
		}
		else
		{
			// if current_time - captured_time > reload time
			if (graphics::getGlobalTime() - lastFiredTime > 500)
				canFire = true;
		}

		auto pp = begin(projectiles);
		while (pp != end(projectiles))
		{
			if (!(*pp)->isAlive())
			{
				delete* pp;
				pp = projectiles.erase(pp);
			}
			else
			{
				(*pp)->update();
				++pp;
			}
		}
	}else
		pos_y -= speed * graphics::getDeltaTime() / 7.0f;
}

void Player::draw()
{
	graphics::Brush br;
	br.outline_opacity = 0.0f;

	// draw projectiles under spaceship
	for (auto pp : projectiles)
		if (pp)
			pp->draw();
	
	if (winAnimation)
	{
	graphics::setOrientation(-90);
	br.texture = std::string(ASSET_PATH) + "blueFlame\\tile0" + std::to_string(flameFrame++ % 60) + ".png";
	graphics::drawRect(pos_x, pos_y + 100, 220, 30, br);
	graphics::resetPose();
	}

	// draw spaceship
	br.texture = std::string(ASSET_PATH) + "player.png";
	graphics::drawRect(pos_x, pos_y, 100, 100, br);

	// draw exhaust flames
	graphics::setOrientation(180);
	br.texture = std::string(ASSET_PATH) + "flame\\tile" + std::to_string(flameFrame++ % 60) + ".png";
	graphics::drawRect(pos_x - 31, pos_y + 45, 10, 40, br);
	graphics::drawRect(pos_x + 31, pos_y + 45, 10, 40, br);
	graphics::resetPose();

	
}

void Player::init()
{
	winAnimation = false;
	canFire = true;
	alive = true;
}

Player::Player()
{
	init();
}

Player::~Player()
{
	for (auto pp : projectiles)
	{
		if (pp)
			delete pp;
	}
}

Hitbox Player::getHitbox()
{
	Hitbox hb;
	hb.cx = pos_x;
	hb.cy = pos_y;
	hb.radius = 35.0f;
	return hb;
}
