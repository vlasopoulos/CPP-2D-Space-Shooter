#pragma once
#include <vector>
#include "enemy.h"
#include "player.h"

class EnemySpawner
{
	std::vector<Enemy*> enemies;
	int maxEnemies;
	bool* isEmpty;
	float lastSpawnTime = 0.0f;
	Player* player = nullptr;
	int deadCount = 0;
public:
	void update();
	void draw();
	void init();
	std::vector<Enemy*> getEnemies() { return enemies; }
	int getDeadCount() { return deadCount; }
	EnemySpawner(int, Player *);
	~EnemySpawner();
};