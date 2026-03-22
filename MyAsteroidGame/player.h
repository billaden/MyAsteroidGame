#pragma once
#include "GameObject.h"
#include "config.h"
#include "shot.h"
#include <string>


class Player : public GameObject ,public Collidable
{
	
	float size;
	float blink;
	float pos_x , pos_y ;
	float speed;
	bool beast;
	bool active; 
	unsigned int score;
	int lifes;
	std::string str;
	std::string name;
	SpaceShip ship;
	noOfPlayer nopl;
	float lastShotTime = 0.0f;
	float shootCooldown = 200.0f; // milliseconds
	

public:
	Player(const class Game& mygame,noOfPlayer no);
	void update() override;
	void draw() override;
	void init() override;
	Disk getCollisionHull() const override;
	//getters
	float getPosX() { return pos_x; };
	float getPosY() { return pos_y; };
	float getSize() { return size / 2; }
	unsigned int getScore() { return score; }
	int getLifes() { return lifes; }
	noOfPlayer getNoOfPlayer() { return nopl; }
	std::string getName() { return name; }
	bool isActive() { return active; }
	bool isBeastMode() { return beast; }
	float getLastShotTime() { return lastShotTime;	}
	float getShootCooldown() { return shootCooldown; }
	

	//setters
	
	void setPosx(float x) { pos_x = x; }
	void setPosY(float y) { pos_y = y; }
	void setActive(bool act) { active = act; }
	void setSpaceShip(SpaceShip sh) { ship = sh; }
	void setBeastMode(bool bm) { beast = bm; }
	void addScore(unsigned int sc) { score += sc; }
	void addLife() { lifes = std::min<int>(10, lifes + 1); }
	void removeLife() { lifes = std::max<int>(0, lifes - 1); }
	void setLastShotTime(float l) {	lastShotTime = l;	}
	void setShootCooldown(float s) { shootCooldown = s; }

	
};
