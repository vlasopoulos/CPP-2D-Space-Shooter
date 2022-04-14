#include "game.h"
#include "graphics.h"
#include "config.h"
#include <ctime>
#include <random>

void Game::updateMenuScreen()
{
	if (graphics::getKeyState(graphics::SCANCODE_SPACE))
	{
		level = 1;
		status = LOADING_SCREEN;
	}
}

void Game::updateLoadingScreen()
{
	
}

void Game::updateGameScreen()
{
	if (!payToWin)
	{
		// update background
		if (bg)
			bg->update();
		// update player
		if (player)
			player->update();
		// update enemies
		if (es)
			es->update();
		// collision
		if (ch)
		{
			ch->checkEnemyCollision();
			ch->checkPlayerCollision();
		}
		//check player alive
		if (player && !player->isAlive()) {
			//dead player
			payToWin = true;
		}
		//check level win condition
		if (es->getDeadCount() >= level * 4 )
		{
			player->playWinAnimation();
			if (player && player->getPlayerPos_y() < -200)
			{ 
				if (++level == 6)
				{
					// game over win screen
					status = WIN_SCREEN;
				}
				else
				{
					status = LOADING_SCREEN;
				}
			}
		}
		// godmode
		if (graphics::getKeyState(graphics::SCANCODE_G) && !gPressed)
		{
			gPressed = true;
			player->enterGodMode();
			graphics::playSound(std::string(ASSET_PATH) + "gepap.mp3", 0.4f);
		}
	}
}

void Game::drawMenuScreen()
{
	graphics::Brush br;
	br.outline_opacity = 0.0f;
	br.texture = std::string(ASSET_PATH) + "menubg.png";
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
	br.fill_color[0] = 0.8f;
	br.fill_color[1] = 0.8f;
	br.fill_color[2] = 0.8f;
	br.fill_opacity = 0.6f;
	std::string s = "ARROW KEYS/WASD to move";
	graphics::drawText(10, 688, 20, s, br);
	s = "SPACE to shoot";
	graphics::drawText(10, 710, 20, s, br);
	br.fill_opacity = 1.0f;
	s = "Press SPACE to Start Game";
	graphics::drawText(CANVAS_WIDTH / 2.8f, CANVAS_HEIGHT / 1.2, 30, s, br);
}

void Game::drawLoadingScreen()
{

	graphics::Brush br;
	br.outline_opacity = 0.0f;
	br.fill_color[0] = 0.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.0f;
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_WIDTH / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.0f;
	std::string s = "LOADING...";
	graphics::drawText(CANVAS_WIDTH / 2.5, CANVAS_HEIGHT / 1.2, 50,  s, br);


	br.fill_opacity = 0.0f;
	for (int i = 0; i < 61; i++) {
		br.texture = std::string(ASSET_PATH) + "playerprojectile\\" + std::to_string(i) + ".png";
		graphics::drawRect(0, 0, 100, 100, br);
		br.texture = std::string(ASSET_PATH) + "enemyprojectile\\tile0" + std::to_string(i) + ".png";
		graphics::drawRect(0, 0, 100, 100, br);
		br.texture = std::string(ASSET_PATH) + "flame\\tile" + std::to_string(i) + ".png";
		graphics::drawRect(0, 0, 100, 100, br);
		br.texture = std::string(ASSET_PATH) + "explosion\\00" + std::to_string(i) + ".png";
		graphics::drawRect(0, 0, 100, 100, br);
		br.texture = std::string(ASSET_PATH) + "blueFlame\\tile0" + std::to_string(i) + ".png";
		graphics::drawRect(0, 0, 100, 100, br);
	}
	br.texture = std::string(ASSET_PATH) + "player.png";
	graphics::drawRect(0, 0, 100, 100, br);
	br.texture = std::string(ASSET_PATH) + "gepap.png";
	graphics::drawRect(0, 0, 100, 100, br);
	levelInit(level);
	status = GAME_SCREEN;
}

void Game::drawGameScreen()
{
	// draw background
	if (bg)
		bg->draw();
	// draw player
	if (player && player->isAlive())
		player->draw();
	// draw enemies
	if (es)
		es->draw();
	// draw explosions
	if (ch)
		ch->drawExplosions();
	// draw ui
	graphics::Brush br;
	br.fill_color[0] = 0.8f;
	br.fill_color[1] = 0.8f;
	br.fill_color[2] = 0.8f;
	br.fill_opacity = 0.5f;
	std::string s = "Level " + std::to_string(level);
	graphics::drawText(10, 700, 40, s, br);
	s = "Kills to escape: " + std::to_string(level * 4 - es->getDeadCount());
	graphics::drawText(1065, 710, 25, s, br);
	if (gPressed)
	{
		br.fill_opacity = 0.8f;
		br.outline_opacity = 0.0f;
		br.texture = std::string(ASSET_PATH) + "gepap.png";
		graphics::drawRect(1250, 670, 60, 60, br);
	}
	else
	{
		s = "HP:";
		graphics::drawText(1063, 685, 30, s, br);
		br.outline_opacity = 0.0f;
		br.fill_opacity = 0.4;
		br.fill_color[0] = 0.0f;
		br.fill_color[1] = 1.0f;
		br.fill_color[2] = 0.0f;
		for (int i = 0; i < int(player->getHitpoints()); i++)
		{
			graphics::drawRect(1140 + 50 * i, 679, 45, 20, br);
	    }
	}
}

void Game::levelInit(int l)
{
	if (bg)
	{
		delete bg;
		bg = nullptr;
	}
	if (player)
	{
		delete player;
		player = nullptr;
	}
	if (es)
	{
		delete es;
		es = nullptr;
	}
	if (ch)
	{
		delete ch;
		ch = nullptr;
	}
	gPressed = false;

	srand((unsigned)time(0));
	graphics::playMusic(std::string(ASSET_PATH) + "cppmusic.wav", 0.5f, true, 2000);
	bg = new Background();
	player = new Player();
	es = new EnemySpawner(level * 2, player);
	ch = new CollisionHandler(player, es);

}

void Game::update()
{
	if (status == MENU_SCREEN)
		updateMenuScreen();
	else if (status == LOADING_SCREEN)
		updateLoadingScreen();
	else if (status == GAME_SCREEN)
		updateGameScreen();
	else if (status == WIN_SCREEN)
	{
		if (graphics::getKeyState(graphics::SCANCODE_RETURN))
		{
			status = MENU_SCREEN;
			graphics::stopMusic();
		}
			
	}
	if (payToWin)
	{
		if (graphics::getKeyState(graphics::SCANCODE_Y))
		{
			status = LOADING_SCREEN;
			payToWin = false;
		}
		if (graphics::getKeyState(graphics::SCANCODE_N))
		{
			graphics::stopMusic();
			status = MENU_SCREEN;
			payToWin = false;
		}
		
	}
}

void Game::draw()
{
	if (status == MENU_SCREEN)
		drawMenuScreen();
	else if (status == LOADING_SCREEN)
		drawLoadingScreen();
	else if (status == GAME_SCREEN)
		drawGameScreen();
	else if (status == WIN_SCREEN)
	{
		graphics::Brush br;
		br.outline_opacity = 0.0f;
		br.texture = std::string(ASSET_PATH) + "winbg.png";
		graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

		//shadows
		br.fill_color[0] = 0.0f;
		br.fill_color[1] = 0.0f;
		br.fill_color[2] = 0.0f;
		graphics::setOrientation(15);
		std::string s = "YOU WIN";
		graphics::drawText(CANVAS_WIDTH / 22 -5.f, CANVAS_HEIGHT / 1.8f -2.f, 100, s, br);
		s = "You've escaped succesfully!";
		graphics::drawText(CANVAS_WIDTH / 30 -3.f, CANVAS_HEIGHT / 1.5f-1.f, 40, s, br);
		// YOU WIN
		br.fill_color[0] = 0.0f;
		br.fill_color[1] = 0.3f;
		br.fill_color[2] = 1.0f;
		graphics::setOrientation(15);
		s = "YOU WIN";
		graphics::drawText(CANVAS_WIDTH / 22, CANVAS_HEIGHT / 1.8f, 100, s, br);

		//shadow
		br.fill_color[0] = 0.2f;
		br.fill_color[1] = 0.7f;
		br.fill_color[2] = 1.0f;		
		s = "You've escaped succesfully!";
		graphics::drawText(CANVAS_WIDTH / 30, CANVAS_HEIGHT / 1.5f, 40, s, br);

		graphics::resetPose();

		br.fill_color[0] = 0.0f;
		br.fill_color[1] = 0.0f;
		br.fill_color[2] = 0.0f;
		s = "Press ENTER to exit to Main Menu";
		graphics::drawText(CANVAS_WIDTH / 25 - 4.f, CANVAS_HEIGHT / 1.04 - 1.f, 30, s, br);
		br.fill_color[0] = 0.9f;
		br.fill_color[1] = 0.9f;
		br.fill_color[2] = 0.9f;
		s = "Press ENTER to exit to Main Menu";
		graphics::drawText(CANVAS_WIDTH / 25, CANVAS_HEIGHT / 1.04, 30, s, br);
	}
	if (payToWin)
	{
		graphics::Brush br;
		br.fill_color[0] = 1.0f;
		br.fill_color[1] = 0.3f;
		br.fill_color[2] = 0.0f;
		std::string s = "YOU LOSE";
		graphics::drawText(CANVAS_WIDTH / 3, CANVAS_HEIGHT / 2, 100, s, br);

		br.fill_color[0] = 0.4f;
		br.fill_color[1] = 1.0f;
		br.fill_color[2] = 0.4f;
		s = "Pay $2.99 to continue on this level? Y/N";
		graphics::drawText(CANVAS_WIDTH / 4.35, CANVAS_HEIGHT / 1.6, 40, s, br);
	}
}

void Game::init()
{
	graphics::setFont(std::string(ASSET_PATH) + "FASTRACE.ttf");
}

Game::Game()
{
}

Game::~Game()
{
	if (player)
		delete player;
	if (es)
		delete es;
	if (bg)
		delete bg;
	if (ch)
		delete ch;
	graphics::stopMusic();
}
