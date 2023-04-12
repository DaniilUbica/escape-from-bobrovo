#pragma once

#include <SFML/Graphics.hpp>
#include <map>

#include "GameObject.h"
#include "Globals.h"
#include "Map.h"
#include "Bullet.h"
#include "CircleBuffer.hpp"
#include "Consumable.h"

class Player : public GameObject {
private:
	State state;
	bool canShoot = true;
	bool canTakeDamage = true;
	cique<Bullet*> bullets;
	sf::Clock clock;
	int damage = 1;

	void Shoot();
public:
	bool isAttacking = false;
	Player(int x, int y, Direction direction, std::map<State, sf::Texture>& textures);
	~Player();

	void Update() override;
	void checkCollision(std::vector<Object> objects);
	void checkBulletCollision(std::vector<Object> objects, GameObject* obj);
	void checkCollisionConsumable(Consumable* consumable);
	void initBullets();

	std::deque<Bullet*> getBullets();

	void setState(State state);

};

