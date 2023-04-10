#pragma once

#include <SFML/Graphics.hpp>
#include <map>

#include "GameObject.h"
#include "Globals.h"
#include "Map.h"
#include "Bullet.h"
#include "CircleBuffer.hpp"

enum State {
	RUN,
	STAY,
	ATTACK,
};

class Player : public GameObject {
private:
	State state;
	bool canShoot = true;
	bool canTakeDamage = true;
	cique<Bullet*> bullets;
	sf::Clock clock;

	void Shoot();
public:
	bool isAttacking = false;
	Player(int x, int y, Direction direction, std::map<State, sf::Texture>& textures);
	~Player();

	void Update() override;
	void checkCollision(std::vector<Object> objects);
	void initBullets();

	std::deque<Bullet*> getBullets();

	void setState(State state);

};

