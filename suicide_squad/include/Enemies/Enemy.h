#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <cmath>

#include "../Player.h"
#include "ViewBorder.h"
#include "View.h"
#include "../UI/HealthBar.h"

class Enemy : public GameObject {
protected:
	State state;
	Player* player;
	bool canAttack = false;
	bool goToFirstPoint = true;
	bool goToSecondPoint = false;
	sf::Clock clock;
	HealthBar* health_bar;

	int point1_x, point2_x, point1_y, point2_y;

	SoundManager s_manager;

	sf::SoundBuffer* attack_sound;

	std::vector<Object> objects;

	void lookForPlayer(float speed);
	void Patrol(float speed);

public:
	ViewBorder* attack_borders;
	View* view_borders;

	~Enemy();

	virtual void Update() = 0;
	void takePlayer(Player* player);
	void takeObjects(std::vector<Object>& objects);
	void setPatrolPoints(int x1, int y1, int x2, int y2);
	void checkCollision(std::vector<Object> objects);
	void setSounds(sf::SoundBuffer& attack);

	HealthBar* getHealthBar();
};