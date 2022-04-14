#include "collisionhandler.h"

bool CollisionHandler::checkCollision(Hitbox h1, Hitbox h2)
{
	float dx = h1.cx - h2.cx;
	float dy = h1.cy - h2.cy;
	if (sqrt(dx * dx + dy * dy) < h1.radius + h2.radius)
		return true;
	return false;
}

void CollisionHandler::playExplosion(Hitbox h)
{
	explosions.push_back(new Explosion(h.cx, h.cy));
}

void CollisionHandler::drawExplosions()
{
	auto e = begin(explosions);
	while (e != end(explosions))
	{
		if ((*e)->hasEnded())
		{
			delete* e;
			e = explosions.erase(e);
		}
		else
		{
			(*e)->draw();
			++e;
		}
	}
}
void CollisionHandler::checkPlayerCollision()
{
	for (auto enemy : es->getEnemies())
	{
		for (auto ep : enemy->getProjectiles())
		{
			if (ep && enemy && p)
			{
				if (checkCollision(ep->getHitbox(), p->getHitbox()))
				{
					playExplosion(ep->getHitbox());
					ep->setDead();
					p->setHit();
				}
			}
		}
	}
}

void CollisionHandler::checkEnemyCollision()
{
	for (auto pp : p->getProjectiles())
	{
		for (auto enemy : es->getEnemies())
		{
			if (pp && enemy)
			{
				if (checkCollision(pp->getHitbox(), enemy->getHitbox()))
				{
					playExplosion(pp->getHitbox());
					pp->setDead();
					enemy->setHit();
				}
			}
		}
	}
}

CollisionHandler::CollisionHandler(Player* player, EnemySpawner* enemySpawner)
{
	p = player;
	es = enemySpawner;
}

CollisionHandler::~CollisionHandler()
{
	for (auto e : explosions)
	{
		if (e)
			delete e;
	}
}
