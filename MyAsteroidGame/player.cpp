#include "player.h"
#include "graphics.h"
#include "scancodes.h"
#include "game.h"

void Player::update()
{
	if(nopl==No1){
		if (graphics::getKeyState(graphics::SCANCODE_D)) {
			pos_x += speed*graphics::getDeltaTime();
		}
		if (graphics::getKeyState(graphics::SCANCODE_A)) {
			pos_x -= speed * graphics::getDeltaTime();
		}
		if (graphics::getKeyState(graphics::SCANCODE_S)) {
			pos_y += speed * graphics::getDeltaTime();
		}
		if (graphics::getKeyState(graphics::SCANCODE_W)) {
			pos_y -= speed * graphics::getDeltaTime();
		}
	}
	else
	{
		if (graphics::getKeyState(graphics::SCANCODE_RIGHT)) {
			pos_x += speed * graphics::getDeltaTime();
		}
		if (graphics::getKeyState(graphics::SCANCODE_LEFT)) {
			pos_x -= speed * graphics::getDeltaTime();
		}
		if (graphics::getKeyState(graphics::SCANCODE_DOWN)) {
			pos_y += speed * graphics::getDeltaTime();
		}
		if (graphics::getKeyState(graphics::SCANCODE_UP)) {
			pos_y -= speed * graphics::getDeltaTime();
		}
	}

	if (pos_x < 0) pos_x = 0;
	if (pos_x > CANVAS_WIDTH) pos_x = CANVAS_WIDTH;
	if (pos_y < 0) pos_y = 0;
	if (pos_y > CANVAS_HEIGHT) pos_y = CANVAS_HEIGHT;

	if (getLifes() == 10) str = "X";
	if (getLifes() == 9) str = "IX";
	if (getLifes() == 8) str = "VIII";
	if (getLifes() == 7) str = "VII";
	if (getLifes() == 6) str = "VI";
	if (getLifes() == 5) str = "V";
	if (getLifes() == 4) str = "IV";
	if (getLifes() == 3) str = "III";
	if (getLifes() == 2) str = "II";
	if (getLifes() == 1) {
		str = "I";
		blink = sinf(graphics::getGlobalTime()/100.0f);
	}

	if (getLifes() == 0) str = "DEAD";

#ifdef DEBUG_PLAYER
	std::cout << "Player " << name << " Update " << std::endl;
	std::cout << pos_x <<" "<< pos_y << " " << size << " " << speed << std::endl;
#endif

}

void Player::draw()
{
	graphics::Brush br,br2;
	br2.outline_opacity = 0.0f;
	br2.fill_opacity = 0.6f;
	br.outline_opacity = 0.0f;

	if(lifes ==1) br.fill_opacity = 1.0f - blink;
	else br.fill_opacity = 1.0f;

	if(beast) graphics::setScale(1.0f, 1.0f);
	else graphics::setScale(0.5f, 0.5f);

		if (nopl == No1) {
			if (isActive()) {
				if (ship == S1) {
					br2.texture = (std::string)ASSET_PATH + "spaceship9-shadow.png";
					br.texture = (std::string)ASSET_PATH + "spaceship9.png";	
				}
				if (ship == S2) {
					br2.texture = (std::string)ASSET_PATH + "spaceship2-shadow.png";
					br.texture = (std::string)ASSET_PATH + "spaceship2.png";
				}
				if (ship == S3) {
					br2.texture = (std::string)ASSET_PATH + "spaceship3-shadow.png";
					br.texture = (std::string)ASSET_PATH + "spaceship3.png";
				}
				if (ship == S4) {
					br2.texture = (std::string)ASSET_PATH + "spaceship4-shadow.png";
					br.texture = (std::string)ASSET_PATH + "spaceship4.png";
				}
				graphics::drawRect(pos_x - 10, pos_y + 20, size, size, br2);
				graphics::drawRect(pos_x, pos_y, size, size, br);
				graphics::resetPose();
				graphics::drawText(pos_x - 22, pos_y - 50, 15, name, br);
				
				
			}
			graphics::resetPose();
			br.texture = "";
			br.fill_opacity = 1.0f;
			graphics::drawText(CANVAS_WIDTH *12/ 100, 25, 30, name, br);
			graphics::drawText(CANVAS_WIDTH *16/ 100, 55, 30, str, br);			
		}
		else {
			if (isActive()) {
				if (ship == S1) {
					br2.texture = (std::string)ASSET_PATH + "spaceship5-shadow.png";
					br.texture = (std::string)ASSET_PATH + "spaceship5.png";
				}
				if (ship == S2) {
					br2.texture = (std::string)ASSET_PATH + "spaceship6-shadow.png";
					br.texture = (std::string)ASSET_PATH + "spaceship6.png";
				}
				if (ship == S3) {
					br2.texture = (std::string)ASSET_PATH + "spaceship7-shadow.png";
					br.texture = (std::string)ASSET_PATH + "spaceship7.png";
				}
				if (ship == S4) {
					br2.texture = (std::string)ASSET_PATH + "spaceship8-shadow.png";
					br.texture = (std::string)ASSET_PATH + "spaceship8.png";
				}
				graphics::drawRect(pos_x - 10, pos_y + 20, size, size, br2);
				graphics::drawRect(pos_x, pos_y, size, size, br);
				graphics::resetPose();
				graphics::drawText(pos_x - 22, pos_y - 50, 15, name, br);
				
				
			}
			graphics::resetPose();
			br.texture = "";
			br.fill_opacity = 1.0f;
			graphics::drawText(CANVAS_WIDTH * 82 / 100, 25, 30, name, br);
			graphics::drawText(CANVAS_WIDTH * 86 / 100, 55, 30, str, br);
			
		}


#ifdef DEBUG_COLLISIONS
		if (isActive()) {
			br.outline_opacity = 1.0f;
			br.texture = "";
			br.fill_color[0] = 0.3f;
			br.fill_color[1] = 1.0f;
			br.fill_color[2] = 0.3f;
			br.fill_opacity = 0.3f;
			br.gradient = false;
			Disk hull = getCollisionHull();
			graphics::drawDisk(hull.cx, hull.cy, hull.radius, br);
		}

#endif // DEBUG

#ifdef DEBUG_PLAYER
	std::cout << "Player " << name <<" Draw " << std::endl;;
	std::cout <<" BeastMOde " <<beast << " Active" << active << " Name " << name <<std::endl;
#endif
	
}

void Player::init()
{
	active = true;
	size = 160.0f;
	blink = 0.0f;
	speed = 0.5f;
	beast = false;
	score = 0;
	lifes = 3;
	if (nopl == No1) {
		setPosx(CANVAS_WIDTH/6);
		setPosY(2*CANVAS_HEIGHT/6);
		name = "RaceTruck";
	}
	else {
		setPosx(CANVAS_WIDTH /6);
		setPosY(4*CANVAS_HEIGHT / 6);
		name = "StarBuck";
	}

#ifdef DEBUG_PLAYER
	std::cout << "Player " << name << " Init "<<std::endl;
	std::cout << " BeastMOde " << beast << " Active" << active  << std::endl;
#endif
}



Disk Player::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	if (beast)disk.radius = size / 2;
	else disk.radius = size / 4;
	return disk;
}



Player::Player(const Game& mygame, noOfPlayer no)
	:GameObject(mygame)
{
	nopl = no;
	init();
}



