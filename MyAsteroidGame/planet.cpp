#include "planet.h"
#include "graphics.h"
#include <iostream>
#include "game.h"


void Planet::update()
{
	Player* player = game.getClosestPlayer(pos_x, pos_y);

	float targetX = player->getPosX();
	float targetY = player->getPosY();

	// desired direction
	float desired_dx = targetX - pos_x;
	float desired_dy = targetY - pos_y;

	// normalize desired
	float length = sqrt(desired_dx * desired_dx + desired_dy * desired_dy);
	if (length != 0) {
		desired_dx /= length;
		desired_dy /= length;
	}

	// SMOOTH TURN
	float turnSpeed = 0.05f; // try 0.02 - 0.1

	dx = dx + (desired_dx - dx) * turnSpeed;
	dy = dy + (desired_dy - dy) * turnSpeed;

	// normalize again (important)
	float len2 = sqrt(dx * dx + dy * dy);
	if (len2 != 0) {
		dx /= len2;
		dy /= len2;
	}

	// move
	pos_x += dx * speed;
	pos_y += dy * speed;
}

void Planet::draw()
{
	graphics::Brush br;
	graphics::setOrientation(0.0f);
	br.outline_opacity = 0.0f;
	br.texture = (std::string)ASSET_PATH + planetfile;
	graphics::drawRect(pos_x,pos_y,size,size,br);
#ifdef DEBUG_PLANET
//	std::cout << "Planet Draw"<< std::endl;
#endif
#ifdef DEBUG_COLLISIONS
	br.outline_opacity = 1.0f;
	br.texture = "";
	br.fill_color[0] = 0.2f;
	br.fill_color[1] = 0.2f;
	br.fill_color[2] = 1.0f;
	br.fill_opacity = 0.3f;
	br.gradient = false;
	Disk hull = getCollisionHull();
	graphics::drawDisk(hull.cx, hull.cy, hull.radius, br);
#endif // DEBUG

}

void Planet::init()
{
	active = true;
	size = 80.0f;
	speed = game.planets_speed + rand0to1()/2;

	randomPlanet();



#ifdef DEBUG_PLANET
	std::cout <<"Planet Init "<<std::endl;
	std::cout << "Planet speed "<<speed << std::endl;
#endif
}

Disk Planet::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = size * 0.5f;
	return disk;
}

Planet::Planet(const Game& mygame, float x, float y)
	: GameObject(mygame), game(mygame)   // ✅ IMPORTANT
{
	init();

	pos_x = x;
	pos_y = y;

	Player* player = game.getPlayer();

	float targetX = player->getPosX();
	float targetY = player->getPosY();

	dx = targetX - pos_x;
	dy = targetY - pos_y;

	float length = sqrt(dx * dx + dy * dy);

	if (length != 0) {
		dx /= length;
		dy /= length;
	}
}

Planet::~Planet()
{
}

void Planet::randomPlanet()
{
	//choose a random type of planet to initiliaze
	float temp = rand0to1();
	if (temp < 0.33f) {
		planetfile = "mars.png";
		planet = Mars;
	}
	else if (temp > 0.67f) {
		planetfile = "earth.png";
		planet = Earth;
	}
	else{
		planetfile = "jupiter.png";
		planet = Jupiter;
	}
}

unsigned int Planet::getDestructionScore()
{
	score = 200 +(unsigned int)( 400.0f * rand0to1());
#ifdef DEBUG_PLANET
	std::cout << score << std::endl;
#endif
	return score;
}


