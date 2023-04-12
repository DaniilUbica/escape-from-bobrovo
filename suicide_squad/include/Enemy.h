#pragma once

#include <SFML/Graphics.hpp>
#include <map>

#include "GameObject.h"
#include "Globals.h"
#include "Map.h"
#include "Bullet.h"
#include "Player.h"
#include "ViewBorder.h"
#include "CircleBuffer.hpp"

class Enemy : public GameObject {
private:
	State state;
	Player* player;
	bool canShoot = false;
	cique<Bullet*> bullets;
	sf::Clock clock;

	void Shoot();
public:
	ViewBorder* borders;
	Enemy(int x, int y, Direction direction, std::map<State, sf::Texture>& textures);
	~Enemy();

	void Update() override;
	void takePlayer(Player* player);
	void initBullets();
	void checkBulletsCollision(std::vector<Object> objects);
	void lookForPlayer();
	void Patrol(int x1, int x2, int y1, int y2);

	std::deque<Bullet*> getBullets();
};

