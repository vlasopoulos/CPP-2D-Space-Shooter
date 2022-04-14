#pragma once

#include "player.h"
#include "enemyspawner.h"
#include "background.h"
#include "collisionhandler.h"

class Game
{
	typedef enum {MENU_SCREEN,LOADING_SCREEN,GAME_SCREEN,WIN_SCREEN} status_t;
	Player * player = nullptr;
	EnemySpawner * es = nullptr;
	Background * bg = nullptr;
	CollisionHandler* ch = nullptr;
	bool payToWin = false;
	int level = 1;
	bool gPressed = false;
	status_t status = MENU_SCREEN;
	void updateMenuScreen();
	void updateLoadingScreen();
	void updateGameScreen();
	void drawMenuScreen();
	void drawLoadingScreen();
	void drawGameScreen();
	void levelInit(int l);
public:
	void update();
	void draw();
	void init();
	Game();
	~Game();
};