#pragma once

#include <SFML/Graphics.hpp>
#include <deque>

#include "../Player.h"

class Turret : public GameObject {
private:
	bool canShoot = true;

	cique<Bullet*> bullets1;
	cique<Bullet*> bullets2;
	cique<Bullet*> bullets3;
	cique<Bullet*> bullets4;

	sf::Clock clock;
public:
	Turret(int coordX, int coordY, sf::Texture& texture);
	~Turret();

	void Update(std::vector<Object> objects, Player* player);
	void Update();
	void initBullets();
	void Shoot();

	std::deque<Bullet*> getBullets1();
	std::deque<Bullet*> getBullets2();
	std::deque<Bullet*> getBullets3();
	std::deque<Bullet*> getBullets4();
};