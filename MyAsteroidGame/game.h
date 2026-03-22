#pragma once
#include "player.h"
#include "meteor.h"
#include "planet.h"
#include "config.h"
#include <list>
#include <iostream>
#include "explosion.h"
#include <set>
#include <time.h>
#include "gifts.h"
#include <queue>


class Game
{
public:
	float planets_speed= 1.0f;
	Player* getPlayer() const;
private:
	
	std::string countdownmessage ="";
	bool playsound = true;
	bool gamestarted = false;
	bool multiplayer = false;
	bool multiplayerMenu = false;
	float gamebegin = 0.0f;
	float beastmodebegin = 0.0f;
	status gamestate = initMenu;
	

	unsigned int noOfMeteors = 2;
	unsigned int score = 0;
	int lifes = 3;
	float fadeout = 0.0f;
	float blink = 0.0f;
	unsigned int windows_width = WINDOW_WIDTH,
		windows_height = WINDOW_HEIGHT;
	clock_t t ;
	float timedelta = 0.0f;
	

	Player* player = nullptr;
	Player* player2 = nullptr;
	Gifts* gift = nullptr;
	Planet* planet = nullptr;
	

	std::list<Meteor> meteors;
	std::list<Shot>  shots;
	std::list<Explosion> explosions;
	std::set<unsigned int,std::greater<unsigned int>> scorelistSingle;
	std::set<unsigned int, std::greater<unsigned int>> scorelistMultiplayer;

	void spawnPlanet();
	void spawnGifts();
	void spawnMeteorite();

	void checkPlayerCollision(Player* player);
	void checkGiftCollision(Player* player);
	void checkShotCollision();
	void createExplosion(float x, float y, TypeOfExplosion tp,float sz);
	void checkLifes(Player* player, Player* player2 = nullptr);



	void drawInit();
	void drawSingle();
	void drawMulti();
	void drawEnterHighscore();
	void drawHighScoreMenu();
	void drawGameOver();

	void drawShots();
	void drawMeteorites();
	void drawExplosion();
	void drawBackground();
	void drawChooseSpaceShip();
	void drawCountingScreen();
	void drawScore();
	void drawPlanetLife();
	void drawBeastModeCounter();
	void drawDebugInfo();
	

	void exitScreen();

	void updateInit();
	void updateChooseSpaceShip();
	void updateCountingScreen();
	void updateSingle();
	void updateMulti();
	void updateEnterHighscore();
	void updateHighScoreMenu();
	void updateGameOver();

	void updateGift();
	void updatePlanet();
	void updateShots();
	void updateMeteorites();
	void updateExplosion();

public:
	void update();
	void draw();
	void init();
	Game();
	~Game();

	void setGamestate(status st);
	status getGamestate();
	unsigned int getScore();
	unsigned int getWindowWidth() { return windows_width; }
	unsigned int getWindowHeight() { return windows_height; }
	void addNoOfMeteors() { noOfMeteors = std::min<int>(10, noOfMeteors + 1); }
	void addPlanetSpeed() { planets_speed = std::min<float>(2.2f, planets_speed + 0.1f); }

	float windows2canvasX(float x);
	float windows2canvasY(float y);
	void setWindowDimensions(unsigned int width, unsigned int height) { windows_width = width; windows_height = height; }
	bool isHighScore();
	bool isTimePassed(float finishtime, float startingtime);
	Player* getClosestPlayer(float x, float y) const;

};