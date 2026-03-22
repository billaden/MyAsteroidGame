#include "gifts.h"
#include "graphics.h"
#include "util.h"
#include <iostream>

void Gifts::update()
{
	graphics::Brush br;
	pos_x -= speed * graphics::getDeltaTime();
	if (type == Destroyer) {
		rotation += 0.1f * graphics::getDeltaTime();
		rotation = fmodf(rotation, 360);
	}
	if (pos_x < -size) {
		setActive(false);
	}
#ifdef DEBUG_GIFTS
	std::cout << "Gift update\n";
#endif // DEBUG_GIFT
}

void Gifts::draw()
{
#ifdef DEBUG_GIFTS
	std::cout << "Gift draw\n";
#endif // DEBUG_GIFT

	graphics::Brush br;
	br.outline_opacity = 0.0f;
	graphics::setOrientation(rotation);
	if (type == Life) br.texture = (std::string)ASSET_PATH + "greencross.png";
	else if (type == Destroyer ) br.texture = (std::string)ASSET_PATH + "deathstar.png";
	else br.texture = (std::string)ASSET_PATH + "potion2.png";

	graphics::drawRect(pos_x,pos_y,size,size,br);
	graphics::setOrientation(0.0f);

#ifdef DEBUG_COLLISIONS
	br.outline_opacity = 1.0f;
	br.texture = "";
	br.fill_color[0] = 0.3f;
	br.fill_color[1] = 0.3f;
	br.fill_color[2] = 1.0f;
	br.fill_opacity = 0.3f;
	br.gradient = false;
	Disk hull = getCollisionHull();
	graphics::drawDisk(hull.cx, hull.cy, hull.radius, br);
#endif // DEBUG
}

void Gifts::init()
{
	active = true;
	size = 40.0f;
	speed = 0.5f;
	rotation = 0.0f;
	randomGift(); 
	pos_x = CANVAS_WIDTH + 1.1f * (float)size;
	pos_y = rand0to1() * CANVAS_HEIGHT;

#ifdef DEBUG_GIFTS
	std::cout << "Gift Type " << type << "pos_x " << pos_x << "pos_y " << pos_y << std::endl;;
#endif // DEBUG_GIFT

}

void Gifts::randomGift()
{
	//40% Gia Life 40% gia Destroyer kai 20% gia Eater
	float temp = rand0to1();
	if (temp < 0.40f) {
		type = Life;
	}
	else if (temp > 0.80f) {
		type = Eater;
	}
	else {
		type = Destroyer;
	}
#ifdef DEBUG_GIFTS
	std::cout << temp<<std::endl;
#endif
}

Gifts::Gifts(const Game& mygame)
	:GameObject(mygame)
{
	init();
}

Disk Gifts::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = size * 0.43f;
	return disk;
}
