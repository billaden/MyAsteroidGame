#pragma once
#include "gameobject.h"
#include "config.h"

class Shot : public GameObject,public Collidable
{
private:
	noOfPlayer player;
	float pos_x, pos_y;
	float speed = 0.6f;
	float orientation = 0.0f;
public:
	bool outOfScreen = false;
public:
	Shot(const class Game& mygame,noOfPlayer nopl,float x = 0,float y =0);
	void update() override;
	void draw() override;
	void init() override;
	void setPosX(float x);
	void setPosY(float y);
	float getPosX();
	float getPosY();
	Disk getCollisionHull() const override;
	bool getOutOfScreen() { return outOfScreen; }

};
