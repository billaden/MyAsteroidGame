#include "explosion.h"
#include "graphics.h"
#include "config.h"
#include <iostream>

void Explosion::update()
{
	fadeout += 0.025f;
	if (fadeout > 1.0f) active = false;
#ifdef DEBUG_EXPLOSION
	std::cout << "Explosion Update " << std::endl;
#endif
}

void Explosion::draw()
{
	graphics::Brush br;
	graphics::setOrientation(0);
	br.outline_opacity = 0.0f;
	br.fill_opacity = 1 - fadeout;

	if (type == PlayerExpl) {
		br.texture = (std::string)ASSET_PATH + "explosionplayer.png";
		//std::cout << "Explosion 1" << std::endl;
	}
	if (type == MeteorExpl){ 
		br.texture = (std::string)ASSET_PATH + "explosionmeteor.png";
	}
	if (type == PlanetExpl) {
		br.texture = (std::string)ASSET_PATH + "explosionplanet.png";
	}
	graphics::drawRect(pos_x, pos_y, size, size, br);


#ifdef DEBUG_EXPLOSION
	std::cout << "Explosion Draw " << std::endl;
	std::cout <<"Explosion Position ( " <<pos_x <<" , "<< pos_y << " ) Size " << size << " Type " << type << std::endl;
#endif
	
}

void Explosion::init()
{
}

Explosion::Explosion(const Game& mygame,float x,float y,TypeOfExplosion tp,float sz)
	:GameObject (mygame)
{
	size = sz;
	pos_x = x;
	pos_y = y;
	type = tp;
	active = true;

	if (type == PlanetExpl) {
		size+=50.0f;
	}
}

Explosion::~Explosion()
{
}
