#pragma once
#include "gameobject.h"
#include "config.h"

class Explosion : public GameObject {

	float pos_x, pos_y;
	float size;
	float fadeout = 0.0f;
	bool active ;
	TypeOfExplosion type;

public:
	void update() override;
	void draw() override;
	void init() override;
	bool isActive() { return active; }

	Explosion(const class Game& mygame,float x ,float y,TypeOfExplosion tp,float sz);
	~Explosion();

};
