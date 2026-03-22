#include "game.h"
#include "graphics.h"
#include "config.h"
#include <iostream>
#include <string>
#include "graphics.h"
#include "fileHandling.h"
#include "util.h"
#include <stdlib.h>
#include <iomanip>
#include <sstream>
#include <Windows.h>



void Game::update()
{
	
	if (gamestate == initMenu) updateInit();
	else if (gamestate == chooseSpaceShip) updateChooseSpaceShip();
	else if (gamestate == countingScreen) updateCountingScreen();
	else if (gamestate == singleMode) updateSingle();
	else if (gamestate == multiMode) updateMulti();
	else if (gamestate == enterHighscoreMenu) updateEnterHighscore();
	else if (gamestate == highscoreMenu) updateHighScoreMenu();
	else updateGameOver();
}

void Game::draw()
{
	if (gamestate == initMenu) drawInit();
	else if (gamestate == chooseSpaceShip) drawChooseSpaceShip();
	else if (gamestate == countingScreen) drawCountingScreen();
	else if (gamestate == singleMode) drawSingle();
	else if (gamestate == multiMode) drawMulti();
	else if (gamestate == enterHighscoreMenu) drawEnterHighscore();
	else if (gamestate == highscoreMenu) drawHighScoreMenu();
	else drawGameOver();
}

void Game::init()
{

	graphics::stopMusic();
	ReadFromFile((std::string)ASSET_PATH + "HighScoreListSingle.txt", scorelistSingle);
	ReadFromFile((std::string)ASSET_PATH + "HighScoreListMultiplayer.txt", scorelistMultiplayer);
#ifdef DEBUG_INIT_MENU
	std::cout <<"Read From File\n";
	for (std::set<unsigned int>::iterator set_it = scorelistSingle.begin(); set_it != scorelistSingle.end(); ++set_it) {
		std::cout << *set_it << "\n";
	}
	for (std::set<unsigned int>::iterator set_it = scorelistMultiplayer.begin(); set_it != scorelistMultiplayer.end(); ++set_it) {
		std::cout << *set_it << "\n";
	}
#endif // DEBUG_MODE
	graphics::playMusic((std::string)ASSET_PATH + "Martin Roth - An Analog Guy In A Digital World.mp3", 1.0f, true,1000);

	if (player) {
		delete player;
		player = nullptr;
	}
	if (player2) {
		delete player2;
		player2 = nullptr;
	}
	multiplayer = false;
	multiplayerMenu = false;
	fadeout = 0.0f;
	playsound = true;
	timedelta = 0.0f;
	noOfMeteors = 2;
	gamestarted = false;
	planets_speed = 1.0f;


	if (!meteors.empty()) {
		meteors.clear();
		//meteor = nullptr;
		
	}
	if (!shots.empty()) {
		shots.clear();
		//shot = nullptr;
	}

	if (!explosions.empty()) {
		explosions.clear();
		//explosion = nullptr;
	}
	if (gift) {
		delete gift;
		gift = nullptr;
	}

	if (planet) {
		delete planet;
		planet = nullptr;
	}
}

Game::Game()
{
}

Game::~Game()
{
	
}

void Game::drawInit(){

	graphics::Brush br;
	br.outline_opacity = 0;
	br.texture =((std::string)ASSET_PATH + "bg_init_menu.png");
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;
	graphics::drawRect(CANVAS_WIDTH/2,CANVAS_HEIGHT/2, CANVAS_WIDTH, CANVAS_HEIGHT,br);
	graphics::setFont((std::string)ASSET_PATH +"type.ttf");
	graphics::drawText(MENU0_X ,MENU0_Y,50,"Asteroid Game",br);
	graphics::drawText(MENU1_X,MENU1_Y, 30, "Single Player", br);
	graphics::drawText(MENU2_X,MENU2_Y, 30, "MultiPlayer", br);
	graphics::drawText(MENU3_X,MENU3_Y, 30, "HighScores", br);
	graphics::drawText(MENU4_X,MENU4_Y, 30, "Exit", br);
#ifdef DEBUG_MODE
	graphics::MouseState mouse;
	graphics::getMouseState(mouse);
	br.texture = "";
	graphics::drawDisk(windows2canvasX((float)mouse.cur_pos_x), windows2canvasY((float)mouse.cur_pos_y), 10, br);
#endif // DEBUG_MODE
	
}

void Game::drawChooseSpaceShip()
{
	graphics::Brush br;
	br.outline_opacity = 0.0f;

	br.texture = (std::string)ASSET_PATH + "bg_choosing_spaceship.png";
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	graphics::drawText(CANVAS_WIDTH * 30 / 100, CANVAS_HEIGHT * 2 / 20, 25, "Its Time to Prove Your Glorious History", br);
	graphics::drawText(CANVAS_WIDTH * 25 / 100, CANVAS_HEIGHT * 3 / 20, 25, "Choose Your Spacecraft carefully and be ready", br);
	graphics::drawText(CANVAS_WIDTH * 38 / 100, CANVAS_HEIGHT * 16 / 20, 15, "You can move your spacecraft with", br);

	graphics::drawText(CANVAS_WIDTH * 24 / 100, CANVAS_HEIGHT * 5.5 / 20, 25, " BeastMode", br);
	br.texture = (std::string)ASSET_PATH + "potion2.png";
	graphics::drawRect(CANVAS_WIDTH * 20 / 100, CANVAS_HEIGHT * 5 / 20, 60, 60, br);

	graphics::drawText(CANVAS_WIDTH * 48 / 100, CANVAS_HEIGHT * 5.5 / 20, 25, " +1 Life", br);
	br.texture = (std::string)ASSET_PATH + "greencross.png";
	graphics::drawRect(CANVAS_WIDTH * 45/ 100, CANVAS_HEIGHT *5/ 20, 60, 60, br);

	graphics::drawText(CANVAS_WIDTH * 70 / 100, CANVAS_HEIGHT * 5.5 / 20, 25, "Destroys All Meteorites", br);
	br.texture = (std::string)ASSET_PATH + "deathstar.png";
	graphics::drawRect(CANVAS_WIDTH * 66/ 100, CANVAS_HEIGHT *5/ 20, 60, 60, br);

	br.outline_opacity = 1.0f;
	br.outline_color[0]=0.8f;
	br.outline_color[1]=0.2f;
	br.outline_color[2]=0.0f;
	if (!multiplayerMenu) {
		graphics::drawText(CANVAS_WIDTH * 43 / 100, CANVAS_HEIGHT * 1 / 20, 25, "Mr. " + player->getName(), br);
		graphics::drawText(CANVAS_WIDTH * 32 / 100, CANVAS_HEIGHT * 17 / 20, 20, "W for UP ,A for LEFT ,D for RIGHT,S for DOWN", br);
		graphics::drawText(CANVAS_WIDTH * 39 / 100, CANVAS_HEIGHT * 18 / 20, 20, "You can Fire with SPACE", br);

		br.texture = (std::string)ASSET_PATH + "spaceship9.png";
		graphics::drawRect(CANVAS_WIDTH / 5, CANVAS_HEIGHT / 2, 100, 100, br);

		br.texture = (std::string)ASSET_PATH + "spaceship2.png";
		graphics::drawRect(CANVAS_WIDTH * 2 / 5, CANVAS_HEIGHT / 2, 100, 100, br);

		br.texture = (std::string)ASSET_PATH + "spaceship3.png";
		graphics::drawRect(CANVAS_WIDTH * 3 / 5, CANVAS_HEIGHT / 2, 100, 100, br);

		br.texture = (std::string)ASSET_PATH + "spaceship4.png";
		graphics::drawRect(CANVAS_WIDTH * 4 / 5, CANVAS_HEIGHT / 2, 100, 100, br);
	}
	else {
		graphics::drawText(CANVAS_WIDTH * 43 / 100, CANVAS_HEIGHT * 1 / 20, 25, "Mr. " + player2->getName(), br);
		graphics::drawText(CANVAS_WIDTH * 35 / 100, CANVAS_HEIGHT * 17 / 20, 20, "Arrows keys UP ,LEFT ,RIGHT,DOWN", br);
		graphics::drawText(CANVAS_WIDTH * 37 / 100, CANVAS_HEIGHT * 18 / 20, 20, "You can Fire with NUM ENTER", br);
		
		br.texture = (std::string)ASSET_PATH + "spaceship5.png";
		graphics::drawRect(CANVAS_WIDTH / 5, CANVAS_HEIGHT / 2, 100, 100, br);

		br.texture = (std::string)ASSET_PATH + "spaceship6.png";
		graphics::drawRect(CANVAS_WIDTH * 2 / 5, CANVAS_HEIGHT / 2, 100, 100, br);

		br.texture = (std::string)ASSET_PATH + "spaceship7.png";
		graphics::drawRect(CANVAS_WIDTH * 3 / 5, CANVAS_HEIGHT / 2, 100, 100, br);

		br.texture = (std::string)ASSET_PATH + "spaceship8.png";
		graphics::drawRect(CANVAS_WIDTH * 4 / 5, CANVAS_HEIGHT / 2, 100, 100, br);
	}

}

void Game::drawCountingScreen()
{
	drawBackground();
	drawScore();

	graphics::Brush br;
	graphics::drawText(450, 250, 50, countdownmessage, br);
	gamestarted = true;

	if (multiplayer) {
		player->draw();
		player2->draw();
	}
	else player->draw();

}

void Game::drawScore()
{
	graphics::Brush br;
	graphics::setOrientation(0);
	br.fill_opacity = 0.5f;
	graphics::drawText(CANVAS_WIDTH * 35/ 100, CANVAS_HEIGHT *5 /100, 20, "Score to Win : ", br);
	graphics::drawText(CANVAS_WIDTH * 24 / 100, CANVAS_HEIGHT * 10 / 100, 20, "Score to Enter Highscore : ", br);
	if (!multiplayer) {
		graphics::drawText(CANVAS_WIDTH * 48 / 100, CANVAS_HEIGHT * 5 / 100, 20, std::to_string(*scorelistSingle.begin()), br);
		graphics::drawText(CANVAS_WIDTH * 48 / 100, CANVAS_HEIGHT * 10 / 100, 20, std::to_string(*scorelistSingle.rbegin()), br);	
	}
	else {
		graphics::drawText(CANVAS_WIDTH * 48 / 100, CANVAS_HEIGHT * 5 / 100, 20, std::to_string(*scorelistMultiplayer.begin()), br);
		graphics::drawText(CANVAS_WIDTH * 48 / 100, CANVAS_HEIGHT * 10 / 100, 20, std::to_string(*scorelistMultiplayer.rbegin()), br);
	}
	br.fill_opacity = 1.0f;
	graphics::drawText(CANVAS_WIDTH * 30/ 100, CANVAS_HEIGHT * 15 / 100, 30, "   Your Score : ", br);
	graphics::drawText(CANVAS_WIDTH * 48/ 100, CANVAS_HEIGHT * 15 / 100, 30, std::to_string(getScore()), br);
}

void Game::drawSingle()
{
	drawBackground();

	if (player) player->draw();
	if (gift) gift->draw();
	if (planet) {
		planet->draw();
		drawPlanetLife();
	}

	drawShots();
	drawMeteorites();
	drawExplosion();

#ifdef DEBUG_INFO
	drawDebugInfo();
#endif

}

void Game::drawMulti()
{
	drawBackground();

	if (player) player->draw();
	if (player2) player2->draw();
	if (gift) gift->draw();
	if (planet) {
		planet->draw();
		drawPlanetLife();
	}
	drawMeteorites();
	drawShots();
	drawExplosion();

#ifdef DEBUG_INFO
	drawDebugInfo();
#endif
}

void Game::drawEnterHighscore()
{
	float glow = 0.5f + 0.5f * sinf(graphics::getGlobalTime() / 50);
	graphics::Brush br;
	br.texture = ((std::string)ASSET_PATH + "bg_highscore_menu.png");
	graphics::drawRect(CANVAS_WIDTH/2,CANVAS_HEIGHT/2, CANVAS_WIDTH, CANVAS_HEIGHT,br);
	br.fill_color[0] = 0.5f + glow;
	br.fill_color[1] = 0.5f;
	br.fill_color[2] = 0.5f + glow;
	graphics::drawText(CANVAS_WIDTH*7.5/20,CANVAS_HEIGHT*3/10,50,"We Have a New",br);
	graphics::drawText(CANVAS_WIDTH*7.5/20,CANVAS_HEIGHT*4/10,50, "Highscore !!!", br);
	graphics::drawText(CANVAS_WIDTH*9/20,CANVAS_HEIGHT*6/10,50,std::to_string(getScore()), br);
	graphics::drawText(CANVAS_WIDTH*30/100,CANVAS_HEIGHT*9/10,30,"Press Enter for HighScore List", br);


}

void Game::drawHighScoreMenu()
{
	graphics::Brush br;
	br.texture = (std::string)ASSET_PATH + "blackwhitegalaxy.png";
	br.outline_opacity = 0.0f;
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
	graphics::drawText(7 * CANVAS_WIDTH / 20, CANVAS_HEIGHT / 10, 60, "HighScores", br);
	br.texture = (std::string)ASSET_PATH + "blackboard.png";
	br.fill_opacity = 0.9f;
	graphics::drawRect(CANVAS_WIDTH*5 / 20, CANVAS_HEIGHT *2/ 3, 300, 540, br);
	graphics::drawRect(CANVAS_WIDTH *15/ 20, CANVAS_HEIGHT *2/ 3, 300, 540, br);
	br.fill_opacity = 1.0f;
	graphics::drawText(3 * CANVAS_WIDTH / 20, CANVAS_HEIGHT *2/ 10, 40, "Single player", br);
	graphics::drawText(13 * CANVAS_WIDTH / 20, CANVAS_HEIGHT*2 / 10, 40, "Multi player", br);
	int i = 1;
	for (std::set<unsigned int>::iterator it = scorelistSingle.begin(); it != scorelistSingle.end(); ++it) {
		if (i < 4) {
			graphics::drawText(3 * CANVAS_WIDTH / 20, CANVAS_HEIGHT * (i + 2) / 10, 50, std::to_string(i) + " .  " + std::to_string(*it), br);
		}
		else {
			graphics::drawText(3 * CANVAS_WIDTH / 20, CANVAS_HEIGHT * (i + 7.5f) / 20, 30, std::to_string(i) + " .  " + std::to_string(*it), br);
		}
		i++;
	}
	i = 1;
	for (std::set<unsigned int>::iterator it = scorelistMultiplayer.begin(); it != scorelistMultiplayer.end(); ++it) {
		if (i < 4) {
			graphics::drawText(13 * CANVAS_WIDTH / 20, CANVAS_HEIGHT * (i + 2) / 10, 50, std::to_string(i) + " .  " + std::to_string(*it), br);
		}
		else {
			graphics::drawText(13 * CANVAS_WIDTH / 20, CANVAS_HEIGHT * (i + 7.5f) / 20, 30, std::to_string(i) + " .  " + std::to_string(*it), br);
		}
		i++;
	}

	br.fill_opacity = 1 - blink;
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 0.0f;
	graphics::drawText(8.5 * CANVAS_WIDTH / 20, CANVAS_HEIGHT * 19 / 20, 20, "Press Enter to Menu", br);
}

void Game::drawGameOver()
{
	graphics::Brush br;
	br.fill_opacity = 1 - fadeout;
	br.fill_color[0] = 1.0f ;
	br.fill_color[1] = 1.0f ;
	br.fill_color[2] = 1.0f ;
	graphics::drawText(8*CANVAS_WIDTH /20, CANVAS_HEIGHT / 2, 50, "Game Over", br); 

	br.fill_opacity = 1 - blink;
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 0.0f;
	graphics::drawText(8.5 * CANVAS_WIDTH / 20, CANVAS_HEIGHT* 19/20, 20, "Press Enter to Menu", br);

}

void Game::drawShots()
{
	if (!shots.empty()) {
		for (std::list <Shot> ::iterator it = shots.begin(); it != shots.end(); ++it) {
				it->draw();
		}
	}
}

void Game::drawMeteorites()
{
	if(!meteors.empty()){
		for (std::list <Meteor> ::iterator met_it = meteors.begin(); met_it != meteors.end(); ++met_it) {
			met_it->draw();
		}
	}
}

void Game::drawExplosion()
{
	if (!explosions.empty()) {
		for (std::list <Explosion> ::iterator exp_it = explosions.begin(); exp_it != explosions.end(); ++exp_it) {
			exp_it->draw();
		}
	}
}

void Game::drawBackground()
{
	graphics::Brush br;
	br.texture = (std::string)ASSET_PATH + "bg_galaxy.png";
	if (!multiplayer && player->isBeastMode())  br.texture = (std::string)ASSET_PATH + "bg_gameplay.png";
	if (multiplayer && (player->isBeastMode()|| player2->isBeastMode()) )  br.texture = (std::string)ASSET_PATH + "bg_gameplay.png";
	
	br.fill_opacity = 0.8f;
	br.outline_opacity = 0.0f;
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
}

void Game::exitScreen()
{
	exit(0);
}

void Game::drawPlanetLife()
{
	float life = planet->getLife();
	float x = planet->getPosX();
	float y = planet->getPosY();
	graphics::Brush br;
	br.outline_opacity = 0.0f;
	br.texture = "";
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 0.2f;
	br.fill_color[2] = 0.0f;
	br.fill_secondary_color[0] = 0.2f;
	br.fill_secondary_color[1] = 0.2f;
	br.fill_secondary_color[2] = 1.0f;
	br.gradient = true;
	br.gradient_dir_u = 1.0f;
	br.gradient_dir_v = 0.0f;
	graphics::drawRect(x-(40.0f-(life*80/2)),y-50,life*80.0f,10,br);
	br.gradient = false;
	br.outline_opacity = 1.0f;
	br.fill_opacity = 0.0f;
	br.outline_width = 0.05f;
	graphics::drawRect(x , y - 50, 80.0f, 10, br);
}

void Game::drawBeastModeCounter() {

	gamestarted = true;
	float temp =(int)( graphics::getGlobalTime() - beastmodebegin)/1000;
	int i = std::max<int>(0,(float)BEASTMODE_DURATION-temp);
	graphics::Brush br;
	br.fill_opacity = 0.5f;
	graphics::drawText(380, 210, 25, "BeastMode ON until", br);
	graphics::drawText(450, 250, 50,std::to_string(i) , br);
}

void Game::drawDebugInfo()
{
	graphics::Brush br;
	br.texture = "";
	br.fill_opacity = 0.7f;
	br.fill_color[0] = 0.0f;
	br.fill_color[1] = 0.8f;
	br.fill_color[2] = 0.0f;
	std::stringstream ss_time,ss_nopl;
	ss_time << std::fixed << std::setprecision(2) << graphics::getGlobalTime() / 1000;
	ss_nopl << std::fixed << std::setprecision(1) << planets_speed;
	std::string s_time = ss_time.str();
	std::string s_nopl = ss_nopl.str();

	if (player) {
		graphics::drawText(250, 400, 20, "Name " + player->getName(), br);
		graphics::drawText(250, 420, 20, "Lifes " + std::to_string(player->getLifes()), br);
		graphics::drawText(250, 440, 20, "Active " + std::to_string(player->isActive()), br);
		graphics::drawText(250, 460, 20, "Beast Mode " + std::to_string(player->isBeastMode()), br);
	}
	graphics::drawText(450, 400, 20, "No Of Meteors  " + std::to_string(noOfMeteors), br);
	graphics::drawText(450, 420, 20, "Speed of Planets  " + s_nopl, br);
	graphics::drawText(450, 440, 20, "Time of Game  " + s_time, br);
	if (planet) graphics::drawText(450, 460, 20, "Planets active " + std::to_string(planet->getTypeOfPlanet()), br);
	if (gift) graphics::drawText(450, 480, 20, "Gift Active  " + std::to_string(gift->getType()), br);

	
	if (player2) {
		graphics::drawText(750, 400, 20, "Name " + player2->getName(), br);
		graphics::drawText(750, 420, 20, "Lifes " + std::to_string(player2->getLifes()), br);
		graphics::drawText(750, 440, 20, "Active " + std::to_string(player2->isActive()), br);
		graphics::drawText(750, 460, 20, "Beast Mode " + std::to_string(player2->isBeastMode()), br);
	}
	
}

void Game::updateInit()
{
	graphics::MouseState mouse;
	graphics::getMouseState(mouse);
	if (mouse.button_left_pressed){
		if (windows2canvasX((float)mouse.cur_pos_x )> MENU1_X && windows2canvasX((float)mouse.cur_pos_x) < MENU1_X+180 && windows2canvasY((float)mouse.cur_pos_y)> MENU1_Y-25  && windows2canvasY((float)mouse.cur_pos_y )< MENU1_Y) {
			#ifdef DEBUG_MODE
			std::cout << "Single Player" << std::endl;
			#endif
			setGamestate(chooseSpaceShip);
			if (!player) {
				player = new Player(*this, No1);
			}	
		}
		if (windows2canvasX((float)mouse.cur_pos_x) >= MENU2_X && windows2canvasX((float)mouse.cur_pos_x)<MENU2_X + 160 && windows2canvasY((float)mouse.cur_pos_y) > MENU2_Y - 25 && windows2canvasY((float)mouse.cur_pos_y) < MENU2_Y) {
			#ifdef DEBUG_MODE
			std::cout << "Multi Player" << std::endl;
			#endif
			setGamestate(chooseSpaceShip);
			multiplayer = true;
			if (!player && !player2) {
				player = new Player(*this, No1);
				player2 = new Player(*this, No2);
			}
		}
		if (windows2canvasX((float)mouse.cur_pos_x) >= MENU3_X && windows2canvasX((float)mouse.cur_pos_x)<MENU3_X + 150 && windows2canvasY((float)mouse.cur_pos_y) > MENU3_Y- 25  && windows2canvasY((float)mouse.cur_pos_y) < MENU3_Y) {
			#ifdef DEBUG_MODE
			std::cout << "Highscores" << std::endl;
			#endif
			setGamestate(highscoreMenu);
		}
		if (windows2canvasX((float)mouse.cur_pos_x )>= MENU4_X && windows2canvasX((float)mouse.cur_pos_x)<MENU4_X + 65 && windows2canvasY((float)mouse.cur_pos_y) > MENU4_Y - 25 && windows2canvasY((float)mouse.cur_pos_y) < MENU4_Y) {
			#ifdef DEBUG_MODE
			std::cout << "Exit" << std::endl;
			#endif
			exitScreen();
		}
	} 
}

void Game::updateChooseSpaceShip()
{

	graphics::MouseState mouse;
	graphics::getMouseState(mouse);

	if (mouse.button_left_pressed) {
		if (windows2canvasX((float)mouse.cur_pos_x) > ((CANVAS_WIDTH / 5) - 50.0f) && windows2canvasX((float)mouse.cur_pos_x) < ((CANVAS_WIDTH / 5)) + 50.0f && windows2canvasY((float)mouse.cur_pos_y) > ((CANVAS_HEIGHT / 2) - 50.0f) && windows2canvasY((float)mouse.cur_pos_y) < ((CANVAS_HEIGHT / 2) + 50.0f)) {
#ifdef DEBUG_MODE
			std::cout << "SpaceShip 1" << std::endl;
#endif
			if (multiplayer) {
				if (!multiplayerMenu) {
					player->setSpaceShip(S1);
					multiplayerMenu = true;
				}
				else {
					player2->setSpaceShip(S1);
					setGamestate(countingScreen);
				}
			}
			else {
				player->setSpaceShip(S1);
				setGamestate(countingScreen);
			}
			t = clock();
			
		}
		if (windows2canvasX((float)mouse.cur_pos_x) > ((CANVAS_WIDTH * 2 / 5) - 50.0f) && windows2canvasX((float)mouse.cur_pos_x) < ((CANVAS_WIDTH * 2 / 5)) + 50.0f && windows2canvasY((float)mouse.cur_pos_y) > ((CANVAS_HEIGHT / 2) - 50.0f) && windows2canvasY((float)mouse.cur_pos_y) < ((CANVAS_HEIGHT / 2) + 50.0f)) {
#ifdef DEBUG_MODE
			std::cout << "SpaceShip 2" << std::endl;
#endif
			if (multiplayer) {
				if (!multiplayerMenu) {
					player->setSpaceShip(S2);
					multiplayerMenu = true;
				}
				else {
					player2->setSpaceShip(S2);
					setGamestate(countingScreen);
				}
			}
			else {
				player->setSpaceShip(S2);
				setGamestate(countingScreen);
			}
			t = clock();
		}
		if (windows2canvasX((float)mouse.cur_pos_x) > ((CANVAS_WIDTH * 3 / 5) - 50.0f) && windows2canvasX((float)mouse.cur_pos_x) < ((CANVAS_WIDTH * 3 / 5)) + 50.0f && windows2canvasY((float)mouse.cur_pos_y) > ((CANVAS_HEIGHT / 2) - 50.0f) && windows2canvasY((float)mouse.cur_pos_y) < ((CANVAS_HEIGHT / 2) + 50.0f)) {
#ifdef DEBUG_MODE
			std::cout << "SpaceShip 3" << std::endl;
#endif
			if (multiplayer) {
				if (!multiplayerMenu) {
					player->setSpaceShip(S3);
					multiplayerMenu = true;
				}
				else {
					player2->setSpaceShip(S3);
					setGamestate(countingScreen);
				}
			}
			else {
				player->setSpaceShip(S3);
				setGamestate(countingScreen);
			}
			t = clock();
		}
		if (windows2canvasX((float)mouse.cur_pos_x) > ((CANVAS_WIDTH * 4 / 5) - 50.0f) && windows2canvasX((float)mouse.cur_pos_x) < ((CANVAS_WIDTH * 4 / 5)) + 50.0f && windows2canvasY((float)mouse.cur_pos_y) > ((CANVAS_HEIGHT / 2) - 50.0f) && windows2canvasY((float)mouse.cur_pos_y) < ((CANVAS_HEIGHT / 2) + 50.0f)) {
#ifdef DEBUG_MODE
			std::cout << "SpaceShip 4" << std::endl;
#endif
			if (multiplayer) {
				if (!multiplayerMenu) {
					player->setSpaceShip(S4);
					multiplayerMenu = true;
				}
				else {
					player2->setSpaceShip(S4);
					setGamestate(countingScreen);
				}
			}
			else {
				player->setSpaceShip(S4);
				setGamestate(countingScreen);
			}
			t = clock();
		}
	}

}

void Game::updateCountingScreen()
{
	
	clock_t temp;
	temp = clock() - t;
	t = clock();
	timedelta += (float)((float)temp / CLOCKS_PER_SEC);
#ifdef DEBUG_COUNTING_SCREEN
	std::cout << "clock " << clock() << std::endl;
	std::cout << "temp " << temp << std::endl;	
	std::cout << "t2 " << t2 << std::endl;
	std::cout <<"timedelta "<< timedelta << std::endl;
#endif
	if ((int)timedelta  == 0) countdownmessage = "Ready ??";
	if ((int)timedelta == 1) countdownmessage = "    3";
	if ((int)timedelta == 2) countdownmessage = "    2";
	if ((int)timedelta == 3) countdownmessage = "    1";
	if ((int)timedelta == 4) countdownmessage = "  Gooo";
	if ((int)timedelta == 5){
		if (multiplayer) setGamestate(multiMode);
		else setGamestate(singleMode);
		gamebegin = graphics::getGlobalTime();
	}

}


void Game::updateSingle()
{
	drawScore();

	if (player) {
		player->update();
		//player->setBeastMode(true);
		checkPlayerCollision(player);
		checkLifes(player);
		if (gift && player->isActive()) checkGiftCollision(player);

		if (player->isBeastMode()) {
			drawBeastModeCounter();
			player->setShootCooldown(20);
			if (isTimePassed(BEASTMODE_DURATION, beastmodebegin)) {
				player->setBeastMode(false);
				player->setShootCooldown(200);
			}
		}

		float now = graphics::getGlobalTime();

		if (player->isActive() &&
			graphics::getKeyState(graphics::SCANCODE_SPACE) &&
			now - player->getLastShotTime() > player->getShootCooldown())
		{
			shots.emplace_back(*this,
				player->getNoOfPlayer(),
				player->getPosX() + (player->isBeastMode() ? 50 : 20),
				player->getPosY());

			player->setLastShotTime(now) ;

			graphics::playSound((std::string)ASSET_PATH + "Golf Ball Hit Gaming.mp3", 0.05f, false);
		}
	}

	
	updateShots();
	updateMeteorites();
	updateExplosion();
	updateGift();
	updatePlanet();

	checkShotCollision();

	spawnMeteorite();

	if (isTimePassed(TIME4PLANET, gamebegin)) spawnPlanet();
	if (isTimePassed(TIME4GIFT, gamebegin)) spawnGifts();

	if (isTimePassed(TIME4MORE_METEORS, gamebegin)) addNoOfMeteors();
	if (isTimePassed(TIME4QUICKER_PLANETS, gamebegin)) addPlanetSpeed();

}

void Game::updateMulti()
{
	drawScore();

	if (player) {
		player->update();
		checkPlayerCollision(player);
		if (gift && player->isActive()) checkGiftCollision(player);

		if (player->isBeastMode()) {
			drawBeastModeCounter();
			player->setShootCooldown(20);
			if (isTimePassed(BEASTMODE_DURATION, beastmodebegin)) {
				player->setBeastMode(false);
				player->setShootCooldown(200);
			}
		}

		float now = graphics::getGlobalTime();

		if (player->isActive() &&
			graphics::getKeyState(graphics::SCANCODE_SPACE) &&
			now - player->getLastShotTime() > player->getShootCooldown())
		{
			shots.emplace_back(*this,
				player->getNoOfPlayer(),
				player->getPosX() + (player->isBeastMode() ? 50 : 20),
				player->getPosY());

			player->setLastShotTime(now);

			graphics::playSound((std::string)ASSET_PATH + "Golf Ball Hit Gaming.mp3", 0.05f, false);
		}
	}

	if(player2){
		player2->update();
		checkPlayerCollision(player2);
		if (gift && player2->isActive()) checkGiftCollision(player2);

		if (player2->isBeastMode()) {
			drawBeastModeCounter();
			player2->setShootCooldown(20);
			if (isTimePassed(BEASTMODE_DURATION, beastmodebegin)) {
				player2->setBeastMode(false);
				player2->setShootCooldown(200);
			}
		}

		float now = graphics::getGlobalTime();

		if (player2->isActive() &&
			graphics::getKeyState(graphics::SCANCODE_KP_ENTER) &&
			now - player2->getLastShotTime() > player2->getShootCooldown())
		{
			shots.emplace_back(*this,
				player2->getNoOfPlayer(),
				player2->getPosX() + (player2->isBeastMode() ? 50 : 20),
				player2->getPosY());

			player2->setLastShotTime(now);

			graphics::playSound((std::string)ASSET_PATH + "Golf Ball Hit Gaming.mp3", 0.05f, false);
		}
		
	}

	//updating
	updateShots();
	updateMeteorites();
	updateExplosion();
	updateGift();
	updatePlanet();

	//Elegxoi
	checkShotCollision();
	if(player||player2) checkLifes(player, player2);
	//Dimiourgou neous filous kai exthrous
	spawnMeteorite();
	if (isTimePassed(TIME4PLANET, gamebegin)) spawnPlanet();
	if (isTimePassed(TIME4GIFT, gamebegin)) spawnGifts();

	//Getting Harder as time pass by
	if (isTimePassed(TIME4MORE_METEORS, gamebegin)) addNoOfMeteors();
	if (isTimePassed(TIME4QUICKER_PLANETS, gamebegin)) addPlanetSpeed();
	
}

void Game::updateHighScoreMenu()
{
	blink += 0.025f;
	if (blink > 1) blink = 0.0f;

	if (graphics::getKeyState(graphics::SCANCODE_RETURN) || graphics::getKeyState(graphics::SCANCODE_KP_ENTER)) {
		setGamestate(initMenu);
		init();
	}

}

void Game::updateEnterHighscore()
{
	if(graphics::getKeyState(graphics::SCANCODE_RETURN )|| graphics::getKeyState(graphics::SCANCODE_KP_ENTER)){
		setGamestate(highscoreMenu);
		Sleep(200);
	}
}

void Game::updateGameOver()
{ 
		fadeout += 0.0025f;
		if (fadeout > 1.0f) fadeout = 1.0f;

		blink += 0.025f;
		if (blink > 1) blink = 0.0f;

		if (graphics::getKeyState(graphics::SCANCODE_RETURN)|| graphics::getKeyState(graphics::SCANCODE_KP_ENTER)) {
			setGamestate(initMenu);
			init();
		}
}



void Game::updateShots()
{
	if (!shots.empty()) {
		for (std::list <Shot> ::iterator s_it = shots.begin(); s_it != shots.end();) {
			s_it->update();
			if (s_it->getOutOfScreen()) {
				s_it = shots.erase(s_it);
			}
			else {
				++s_it;
			}
		}
	}
}

void Game::updateMeteorites()
{
	if (!meteors.empty()) {
		for (std::list <Meteor> ::iterator m_it = meteors.begin(); m_it != meteors.end();) {
			m_it->update();
			//std::cout << "dx: " << m_it->dirX << " dy: " << dirY << " speed: " << speed << std::endl;
			if (!m_it->isActive()) {
				m_it = meteors.erase(m_it);
			}
			else
				++m_it;
		}
	}

}

void Game::updateGift()
{
	if (gift) {
		gift->update();
		if (!gift->isActive()) {
			delete gift;
			gift = nullptr;
		}
	}
}

void Game::updateExplosion()
{	
	if (!explosions.empty()) {
		for (std::list <Explosion> ::iterator exp_it = explosions.begin(); exp_it != explosions.end();) {
			exp_it->update();
			if (!exp_it->isActive()) {
				exp_it = explosions.erase(exp_it);
			}
			else
				++exp_it;
		}
	}
}

void Game::updatePlanet()
{
	if (planet) {
		planet->update();
		if (!planet->isActive()) {
			delete planet;
			planet = nullptr;
		}
	}
}


void Game::spawnGifts()
{
	if (!gift) {
#ifdef DEBUG_GIFTS
		std::cout << "New Gift \n";
#endif // DEBUG
		gift = new Gifts(*this);
	}
}

void Game::spawnPlanet()
{
	if (!planet) {
#ifdef DEBUG_PLANET
		std::cout << "New Planet \n";
#endif // DEBUG
		int side = rand() % 3;

		float x, y;

		if (side == 0) { // RIGHT
			x = CANVAS_WIDTH + 50.0f;
			y = 50.0f + rand0to1() * (CANVAS_HEIGHT - 100.0f);
		}
		else if (side == 1) { // TOP
			x = rand0to1() * CANVAS_WIDTH;
			y = -50.0f;
		}
		else { // BOTTOM
			x = rand0to1() * CANVAS_WIDTH;
			y = CANVAS_HEIGHT + 50.0f;
		}

		planet = new Planet(*this, x, y);
	}
}

void Game::spawnMeteorite()
{
	float elapsed = (graphics::getGlobalTime() - gamebegin) / 1000.0f;

    if (meteors.size() < noOfMeteors) {
        // Generate random position, size, and speed for the new meteor
        float x = CANVAS_WIDTH + 50.0f; // spawn just outside right edge
        float y = 50.0f + rand0to1() * (CANVAS_HEIGHT - 100.0f); // random y within canvas
        float size = 60.0f + rand0to1() * 80.0f; // size between 60 and 140
		float baseSpeed = 0.03f+ rand0to1() * 0.1f;

		// increase over time
		float speedMultiplier = std::min<float>(3.0f, 1.0f + elapsed * 0.05f);

		float speed = baseSpeed * speedMultiplier;


		noOfMeteors = 2 + (int)(elapsed / 10);

        std::string meteorname, meteorshadowname;
        chooseMeteor(meteorname, meteorshadowname);

        meteors.emplace_back(*this, x, y, size, speed, meteorname, meteorshadowname);
    }

#ifdef DEBUG_METEORS
    std::cout << "No of Meteors " << noOfMeteors << std::endl;
#endif
}



void Game::checkPlayerCollision(Player* player)
{
	unsigned int score = 0;
	if (player->isActive()) {
		Disk d1 = player->getCollisionHull();
		if (!meteors.empty()) {
			for (std::list <Meteor> ::iterator m_it = meteors.begin(); m_it != meteors.end();) {
					Disk d2 = m_it->getCollisionHull();
					float dx = d1.cx - d2.cx;
					float dy = d1.cy - d2.cy;
					if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius) {
#ifdef DEBUG_PLAYER_COLLISION
						std::cout << "Explosion Point ( " << player->getPosX() + 38 << " ," << player->getPosY() << " )" << std::endl;
						std::cout << "boom" << std::endl;
#endif // DEBUG
						if (!player->isBeastMode()) {
							player->removeLife();
							createExplosion(player->getPosX() + 38, player->getPosY(), PlayerExpl, player->getSize());
						}
						else
						{
							score += m_it->getDestructionScore();
							createExplosion(m_it->getPosX(), m_it->getPosY(), MeteorExpl, m_it->getSize());
						}
						m_it = meteors.erase(m_it);
					}
					if (m_it != meteors.end()) ++m_it;
			}
		}
		if (planet) {
			Disk d3 = planet->getCollisionHull();
			float dx = d1.cx - d3.cx;
			float dy = d1.cy - d3.cy;
			if (sqrt(dx * dx + dy * dy) < d1.radius + d3.radius) {
				if (!player->isBeastMode()) {
					player->removeLife();
					createExplosion(player->getPosX() + 38, player->getPosY(), PlayerExpl, player->getSize());

				}
				else {
					createExplosion(planet->getPosX(), planet->getPosY(), PlanetExpl, planet->getSize());
					score += planet->getDestructionScore();
				}
				delete planet;
				planet = nullptr;
			}
		}

	}
	player->addScore(score);

}

void Game::checkGiftCollision(Player* player)
{
	Disk d1 = player->getCollisionHull();
	Disk d2 = gift->getCollisionHull();
	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;
	if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius) {
		if (gift->getType() == Life) {
			player->addLife();
		}
		else if (gift->getType() == Destroyer)
		{
			unsigned int score = 0;

			// destroy meteors
			for (std::list<Meteor>::iterator m_it = meteors.begin(); m_it != meteors.end(); ++m_it) {
				score += m_it->getDestructionScore();
				createExplosion(m_it->getPosX(), m_it->getPosY(), MeteorExpl, m_it->getSize());
			}
			meteors.clear();

			// destroy planet 
			if (planet) {
				score += planet->getDestructionScore();
				createExplosion(planet->getPosX(), planet->getPosY(), PlanetExpl, planet->getSize());

				delete planet;
				planet = nullptr;
			}

			player->addScore(score);
		}
		else {
			player->setBeastMode(true);
			beastmodebegin = graphics::getGlobalTime();
		}
		graphics::playSound((std::string)ASSET_PATH + "MarioCoin.mp3", 0.5f);
		delete gift;
		gift = nullptr;
	}

}



void Game::checkShotCollision()
{
	
	if (!meteors.empty() && !shots.empty()) {
#ifdef DEBUG_SHOT_COLL
		//std::cout<<"checkShotColision"<<std::endl;
#endif // DEBUG_MODE
		unsigned int score = 0;
		for (std::list <Shot> ::iterator s_it = shots.begin(); s_it != shots.end();) {
			Disk d1 = s_it->getCollisionHull();
			if (planet) {
				Disk d3 = planet->getCollisionHull();
				float dx = d1.cx - d3.cx;
				float dy = d1.cy - d3.cy;
				if (sqrt(dx * dx + dy * dy) < d1.radius + d3.radius) { 
					planet->reduceLife(0.34f);
					s_it = shots.erase(s_it);
					if (planet->getLife() == 0) {
						score += planet->getDestructionScore();
						createExplosion(planet->getPosX(),planet->getPosY(),PlanetExpl,planet->getSize());
						delete planet;
						planet = nullptr;
						
					}
				}
			}
			for (std::list <Meteor> ::iterator m_it = meteors.begin(); m_it != meteors.end();) {
					Disk d2 = m_it->getCollisionHull();
					float dx = d1.cx - d2.cx;
					float dy = d1.cy - d2.cy;
					if ((sqrt(dx * dx + dy * dy) < d1.radius + d2.radius)) {
						score += m_it->getDestructionScore();
						graphics::playSound((std::string)ASSET_PATH + "RockBreaks.mp3", 0.1f);
#ifdef DEBUG_SHOT_COLL
						//	std::cout << (int)((m_it->getSpeed() ) / (m_it->getSize() ))<< std::endl;
						//	std::cout << "Shot BOOM" << std::endl;
						std::cout << "Speed of Destructed Meteor " << (int)(100 * m_it->getSpeed()) << " 2500 /Size  " << (int)(2500 / m_it->getSize()) << " Total Score " << m_it->getDestructionScore() << std::endl;
#endif // DEBUG			
						float x = m_it->getPosX();
						float y = m_it->getPosY();
						float sz = m_it->getSize();
						float sp = m_it->getSpeed();
						std::string str = m_it->getMeteorName();
						std::string str2 = m_it->getMeteorShadowName();

						//  split happens HERE
						if (sz > 80) {
							meteors.emplace_back(*this, x, y + 30, sz / 2, sp, str, str2);
							meteors.emplace_back(*this, x, y - 30, sz / 2, sp, str, str2);
						}

						m_it = meteors.erase(m_it);
						s_it = shots.erase(s_it);

						continue;
					}
				++m_it;
			}
			++s_it;

			
		}
		
		player->addScore(score);
		//An yparxei collision me meteoriti kai aytos einai megalyteros apo 80 na spaei se 2 kommatia.

	}
}


void Game::createExplosion(float x, float y,TypeOfExplosion tp,float sz)
{
	explosions.emplace_back(*this, x, y, tp, sz);
	graphics::playSound((std::string)ASSET_PATH + "Big Explosion Effect.mp3", 0.5f);
}

void Game::checkLifes(Player* player, Player* player2)
{
	if (player) {
		if (player->getLifes() == 0) {
			player->setActive(false);
		}
	}

	if (player2) {
		if (player2->getLifes() == 0) {
			player2->setActive(false);
		}
	}

	if (!player->isActive() && (!player2 || !player2->isActive())) {
		graphics::stopMusic();
		if (isHighScore()) {
			if (!multiplayer) WriteToFile((std::string)ASSET_PATH + "HighScoreListSingle.txt", scorelistSingle);
			else WriteToFile((std::string)ASSET_PATH + "HighScoreListMultiplayer.txt", scorelistMultiplayer);

			setGamestate(enterHighscoreMenu);
			graphics::playMusic((std::string)ASSET_PATH + "Epic Win - Sound Effect.mp3", 0.8f, false);
			Sleep(500);
		}
		else {
			setGamestate(gameoverMenu);
			graphics::playMusic((std::string)ASSET_PATH + "Sad Trombone.mp3", 0.8f, false);
			Sleep(1000);
		}
	}


}

void Game::setGamestate(status st)
{
	gamestate = st;
}

status Game::getGamestate()
{
	return gamestate;;
}

unsigned int Game::getScore()
{
	if (player && player2) return player->getScore() + player2->getScore();
	else if (player) return player->getScore();
	else return 0;
}

float Game::windows2canvasX(float x)
{
	return x * CANVAS_WIDTH / (float)windows_width;
}

float Game::windows2canvasY(float y)
{
	return y * CANVAS_HEIGHT / (float)windows_height;
}

bool Game::isHighScore()
{
	if (!multiplayer) {
		if (getScore() > *scorelistSingle.rbegin()) {
			scorelistSingle.insert(getScore());
			scorelistSingle.erase(*scorelistSingle.rbegin());
			return true;
		}
	}
	else {
		if (getScore() > *scorelistMultiplayer.rbegin()) {
			scorelistMultiplayer.insert(getScore());
			scorelistMultiplayer.erase(*scorelistMultiplayer.rbegin());
			return true;
		}

	}
	return false;
}


bool Game::isTimePassed(float finishtime, float startingtime) {

	//metrima xronou me akriveia ena dekadiko
	float temp = startingtime;
	float temp2 = graphics::getGlobalTime() - temp;
	float temp3 = finishtime * 1000.0f;

	//	std::cout << " temp  " << (temp2 % temp3) + 2 << " temp3  " << temp3<< std::endl;
	if (fmodf(temp2,temp3) + 100.0f > temp3) return true;
	else return false;

}

Player* Game::getPlayer() const
{
	return player;
}

Player* Game::getClosestPlayer(float x, float y) const
{
	if (player && player2) {
		float dx1 = player->getPosX() - x;
		float dy1 = player->getPosY() - y;
		float d1 = sqrt(dx1 * dx1 + dy1 * dy1);

		float dx2 = player2->getPosX() - x;
		float dy2 = player2->getPosY() - y;
		float d2 = sqrt(dx2 * dx2 + dy2 * dy2);

		return (d1 < d2) ? player : player2;
	}

	if (player) return player;
	if (player2) return player2;

	return nullptr;
}