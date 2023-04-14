#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <cmath>

#include "GameObject.h"
#include "Globals.h"
#include "Map.h"
#include "Bullet.h"
#include "Player.h"
#include "ViewBorder.h"
#include "CircleBuffer.hpp"
#include "HealthBar.h"

const int HP = 3;

class Enemy : public GameObject {
private:
	State state;
	Player* player;
	bool canShoot = false;
	bool goToFirstPoint = true;
	bool goToSecondPoint = false;
	cique<Bullet*> bullets;
	sf::Clock clock;
	sf::Sprite hp[HP];
	HealthBar* health_bar;

	int point1_x, point2_x, point1_y, point2_y;

	void Shoot();
	void initBullets();
	void lookForPlayer();
	void Patrol();

public:
	ViewBorder* shoot_borders;
	ViewBorder* view_borders;
	Enemy(int x, int y, Direction direction, std::map<State, sf::Texture>& textures, int health);
	~Enemy();

	void Update() override;
	void takePlayer(Player* player);
	void checkBulletsCollision(std::vector<Object> objects);
	void setPatrolPoints(int x1, int y1, int x2, int y2);
	void checkCollision(std::vector<Object> objects);

	std::deque<Bullet*> getBullets();
	HealthBar* getHealthBar();
};

