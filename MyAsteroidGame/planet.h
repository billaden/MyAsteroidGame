#pragma once
#include "config.h"
#include "gameobject.h"


class Planet :public GameObject, public Collidable {

	float pos_x, pos_y;
	float size;
	float speed;
	bool active;
	float life = 1.0f;
	unsigned int  score;
	TypeOfPlanet planet;
	std::string planetfile;
	float dx = 0.0f;
	float dy = 1.0f;
	const Game& game;

public:
	void update() override;
	void draw() override;
	void init() override;
	Disk getCollisionHull() const override;

	Planet(const class Game& mygame,float x,float y);

	~Planet();

	bool isActive() { return active; }
	void randomPlanet();
	float getLife() { return life; }
	void reduceLife(float amount) { life = std::max<float>(0.0f, life - amount); }
	float getPosX() { return pos_x; }
	float getPosY() { return pos_y; }
	unsigned int  getDestructionScore();
	float getSize() { return size; }
	TypeOfPlanet getTypeOfPlanet() { return planet; }


};

