#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <cmath>

#include "GameObject.h"
#include "Globals.h"
#include "MapObject.h"
#include "Bullet.h"
#include "Player.h"
#include "ViewBorder.h"
#include "CircleBuffer.hpp"
#include "HealthBar.h"

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

	void lookForPlayer(float speed);
	void Patrol(float speed);

public:
	ViewBorder* attack_borders;
	ViewBorder* view_borders;

	~Enemy();

	virtual void Update() = 0;
	void takePlayer(Player* player);
	void setPatrolPoints(int x1, int y1, int x2, int y2);
	void checkCollision(std::vector<Object> objects);

	HealthBar* getHealthBar();
};

class RangeEnemy : public Enemy {
private:
	cique<Bullet*> bullets;

	void Shoot();
	void initBullets();
	float player_shoot_x;
	float player_shoot_y;
public:
	RangeEnemy(int x, int y, Direction direction, std::map<State, sf::Texture>& textures, int health);
	RangeEnemy(int x, int y, Direction direction, sf::Texture& texture, int health);

	void checkBulletsCollision(std::vector<Object> objects);
	void Update() override;

	std::deque<Bullet*> getBullets();
};

class MeleeEnemy : public Enemy {
private:
	void Hit();
public:
	MeleeEnemy(int x, int y, Direction direction, std::map<State, sf::Texture>& textures, int health);
	MeleeEnemy(int x, int y, Direction direction, sf::Texture& texture, int health);
	void Update() override;
};