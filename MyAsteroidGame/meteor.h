#pragma once
#include "gameobject.h"
#include "graphics.h"

class Meteor :public GameObject ,public Collidable
{
	std::string meteorname, meteorshadowname;
	float pos_x, pos_y, new_x, new_y, new_size, new_speed;
	float size;
	float rotation;
	float speed ;
	bool active ;
	bool respawned;
	graphics::Brush brush;

public:
	void update() override;
	void draw() override;
	void init() override;
	Disk getCollisionHull() const override;

	bool isActive() { return active; }
	float getSpeed() { return speed; }
	float getPosX() { return pos_x; }
	float getPosY() { return pos_y; }
	int getDestructionScore();
	float getSize() { return size; }
	std::string getMeteorName() { return meteorname; }
	std::string getMeteorShadowName() { return meteorshadowname; }

	Meteor(const class Game& mygame,float x=0,float y=0, float sz= 0, float sp=0,std::string  str= "", std::string  str2 = "");
	~Meteor();
};