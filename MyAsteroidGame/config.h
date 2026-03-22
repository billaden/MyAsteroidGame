#pragma once

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 600
#define CANVAS_WIDTH 1000
#define CANVAS_HEIGHT 500
#define ASSET_PATH "assets//"
#define MENU0_X (CANVAS_WIDTH /2)-170
#define MENU0_Y 2* CANVAS_HEIGHT / 10
#define MENU1_X (CANVAS_WIDTH /2)-100
#define MENU1_Y 4* CANVAS_HEIGHT / 10
#define MENU2_X (CANVAS_WIDTH /2)-85
#define MENU2_Y 5* CANVAS_HEIGHT / 10
#define MENU3_X (CANVAS_WIDTH /2)-80
#define MENU3_Y 6* CANVAS_HEIGHT / 10
#define MENU4_X (CANVAS_WIDTH /2)-40
#define MENU4_Y 7* CANVAS_HEIGHT / 10

#define TIME4GIFT 15 
#define TIME4PLANET 5
#define BEASTMODE_DURATION 12
#define TIME4MORE_METEORS 16
#define TIME4QUICKER_PLANETS 15
#define MAX_METEORS 9


//#define DEBUG_MODE
//#define DEBUG_COLLISIONS
//#define DEBUG_INFO
//#define DEBUG_PLAYER
//#define DEBUG_GIFTS
//#define DEBUG_PLANET
//#define DEBUG_METEOR
//#define DEBUG_EXPLOSION
//
//
#define DEBUG_METEOR_SPAWN
//#define DEBUG_SHOT_COLL
//#define DEBUG_PLAYER_COLLISION
//
//#define DEBUG_INIT_MENU



typedef enum {initMenu,singleMode,multiMode,enterHighscoreMenu,highscoreMenu,gameoverMenu,chooseSpaceShip,countingScreen} status ;
typedef enum {No1,No2} noOfPlayer;
typedef enum { Life, Destroyer,Eater} TypeOfGift;
typedef enum  { S1 , S2 , S3 , S4 } SpaceShip;
typedef enum {Mars,Earth,Jupiter} TypeOfPlanet;
typedef enum { MeteorExpl, PlanetExpl, PlayerExpl } TypeOfExplosion;