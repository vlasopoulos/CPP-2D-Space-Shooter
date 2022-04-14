#pragma once
#include "player.h"
#include "enemyspawner.h"
#include "explosion.h"

class CollisionHandler
{
	Player* p = nullptr;
	EnemySpawner* es = nullptr;
	bool checkCollision(Hitbox,Hitbox);
	void playExplosion(Hitbox);
	std::vector<Explosion*> explosions;
public:
	void drawExplosions();
	void checkPlayerCollision();
	void checkEnemyCollision();
	CollisionHandler(Player* ,EnemySpawner*);
	~CollisionHandler();
};