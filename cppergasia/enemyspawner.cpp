#include "enemyspawner.h"
#include "graphics.h"

void EnemySpawner::update()
{
	if (graphics::getGlobalTime() - lastSpawnTime > 2000.0f) {
		int i = rand() % maxEnemies;
		if (isEmpty[i])
		{
			enemies.push_back(new Enemy(float(i), float(maxEnemies), player));
			isEmpty[i] = false;
			lastSpawnTime = graphics::getGlobalTime();
		}
	}

	auto enemy = begin(enemies);
	while (enemy != end(enemies))
	{
		if (!(*enemy)->isAlive())
		{
			int temp = int((*enemy)->getPosition());
			isEmpty[temp] = true;
			//death explosion animation
			++deadCount;
			delete* enemy;
			enemy = enemies.erase(enemy);

		}
		else
		{
			(*enemy)->update();
			++enemy;
		}
	}
}

void EnemySpawner::draw()
{
	for (auto enemy : enemies)
	{
		if (enemy)
			enemy->draw();
	}
}

void EnemySpawner::init()
{
	isEmpty = new bool[maxEnemies];
	for (int i = 0; i < maxEnemies; i++) 
	{
		isEmpty[i] = true;
	}
}

EnemySpawner::EnemySpawner(int num,  Player * p)
{
	player = p;
	maxEnemies = num;
	init();
}

EnemySpawner::~EnemySpawner()
{
	delete[] isEmpty;
}
