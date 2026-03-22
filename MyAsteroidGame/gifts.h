#pragma once
#include "gameobject.h"
#include "config.h"

class Gifts :public GameObject, public Collidable {

	float pos_x, pos_y;
	float size ;
	float rotation;
	float speed ;
	TypeOfGift type;
	bool active;


public:
	void update() override;
	void draw() override;
	void init() override;
	Disk getCollisionHull() const override;

	Gifts(const class Game& mygame);
	bool isActive() { return active; }
	void setActive(bool ac) { active = ac; }
	void randomGift();
	TypeOfGift getType() { return type; }



};