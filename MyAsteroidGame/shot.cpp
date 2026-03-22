#include "shot.h"
#include "game.h"
#include "gameobject.h"

Shot::Shot(const Game& mygame,noOfPlayer nopl,float x,float y )
	:GameObject(mygame)
{
	player = nopl;
	pos_x = x;
	pos_y = y;
}

void Shot::update()
{
	pos_x += speed * graphics::getDeltaTime();
	if (pos_x > CANVAS_WIDTH) outOfScreen = true;

}

void Shot::draw()
{
	graphics::Brush br;
	br.outline_opacity = 0.0f;
	br.gradient = true;
	br.gradient_dir_u = 1.0f;
	br.gradient_dir_v = 0.0f;
	graphics::setOrientation(0.0f);

	if (player == No1) {
		br.fill_color[0] = 1.0f;
		br.fill_color[1] = 0.0f;
		br.fill_color[2] = 0.0f;
		br.fill_opacity = 0.8f;
		br.fill_secondary_color[0] = 0.5f;
		br.fill_secondary_color[1] = 0.5f;
		br.fill_secondary_color[2] = 0.0f;
		br.fill_secondary_opacity = 1.0f;
	}
	else {

		br.fill_color[0] = 0.0f;
		br.fill_color[1] = 0.0f;
		br.fill_color[2] = 1.0f;
		br.fill_opacity = 0.8f;
		br.fill_secondary_color[0] = 0.0f;
		br.fill_secondary_color[1] = 1.0f;
		br.fill_secondary_color[2] = 0.0f;
		br.fill_secondary_opacity = 1.0f;
	}
	graphics::drawRect(pos_x, pos_y, 20, 7, br);


#ifdef DEBUG_COLLISIONS
	br.outline_opacity = 1.0f;
	br.texture = "";
	br.fill_color[0] = 0.3f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 0.3f;
	br.fill_opacity = 0.3f;
	br.gradient = false;
	Disk hull = getCollisionHull();
	graphics::drawDisk(hull.cx, hull.cy, hull.radius, br);
#endif // DEBUG
}

void Shot::init()
{
}

void Shot::setPosX(float x)
{
	pos_x = x;
}

void Shot::setPosY(float y)
{
	pos_y = y;
}

float Shot::getPosX() {
	return pos_x;
}

Disk Shot::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x+3;
	disk.cy = pos_y;
	disk.radius = 4;
	return disk;
}

float Shot::getPosY() {
	return pos_y;
}