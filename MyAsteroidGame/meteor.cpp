#include "meteor.h"
#include "config.h"
#include "util.h"
#include <iostream>
#include "game.h"

void Meteor::update()
{
	pos_x -= speed * graphics::getDeltaTime();
	rotation += 0.03f * graphics::getDeltaTime();
	rotation = fmodf(rotation, 360);

	if (pos_x < -size) {
		active = false ;
	}

#ifdef DEBUG_METEORS
	std::cout << "Meteor Update ";
#endif
}

void Meteor::draw()
{
#ifdef DEBUG_METEORS
	std::cout << "Meteor Draw ";
	std::cout <<"Meteor position ( "<< pos_x <<" , "<< pos_y << " ) Size " << size << " Rotation " << rotation << std::endl;
#endif
	
	graphics::setOrientation(rotation);
	brush.outline_opacity = 0.0f;
	brush.fill_opacity = 0.3f;
	brush.texture = (std::string)ASSET_PATH + meteorshadowname;
	graphics::drawRect(pos_x-10, pos_y+20, size, size, brush);
	brush.fill_opacity = 1.0f;
	brush.texture = (std::string)ASSET_PATH + meteorname;
	graphics::drawRect(pos_x,pos_y,size,size,brush);
	graphics::resetPose();

#ifdef DEBUG_COLLISIONS
	brush.outline_opacity = 1.0f;
	brush.texture = "";
	brush.fill_color[0] = 1.0f;
	brush.fill_color[1] = 0.3f;
	brush.fill_color[2] = 0.3f;
	brush.fill_opacity = 0.3f;
	brush.gradient = false;
	Disk hull = getCollisionHull();
	graphics::drawDisk(hull.cx, hull.cy, hull.radius, brush);
#endif // DEBUG
}

void Meteor::init()
{
	active = true;

	if (!respawned) {
		speed = 50.0f + 150.0f * rand0to1();
		size = 50.f + rand0to1()* 100;
		pos_x = CANVAS_WIDTH + 1.1f * (float)size;
		pos_y = (float)(rand0to1() * 500);
		chooseMeteor(meteorname, meteorshadowname);
	}
	
	rotation =(float) (rand() % 360);
	brush.outline_opacity = 0.0f;

#ifdef DEBUG_METEORS
	std::cout << "Meteor Init "<< std::endl;
	
#endif // DEBUG_MODE


}

Disk Meteor::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = size*0.5f;
	return disk;
}

int Meteor::getDestructionScore()
{
	//score katastrofis analogo tis taxytitas kai antistrofos analogo tou megethous tou meteorith
	return (int)(100  * getSpeed()) + (int)(2500 / getSize());
}

Meteor::Meteor(const Game& mygame, float x, float y, float sz, float sp, std::string str, std::string str2)
	:GameObject(mygame)
{
	if (x == 0 && y == 0) respawned = false;
	else {
		respawned = true;
		pos_x = x;
		pos_y = y;
		size = sz;
		speed = sp;
		meteorname = str;
		meteorshadowname = str2;
	}
	init();
}

Meteor::~Meteor()
{
}

