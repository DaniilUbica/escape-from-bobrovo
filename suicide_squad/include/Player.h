#pragma once

#include <SFML/Graphics.hpp>
#include <map>

#include "GameObject.h"
#include "Globals.h"
#include "Map.h"
#include "Bullet.h"
#include "CircleBuffer.hpp"
#include "Consumable.h"

enum Person {
	VOLKOV,
};

class Player : public GameObject {
private:
	Person person;
	State state;

	bool canShoot = true;
	bool canTakeDamage = true;
	bool isVisible = true;
	bool isUltimateWorking = false;

	cique<Bullet*> bullets;
	sf::Clock clock;
	sf::Clock buffs_clock;
	sf::Clock ultimate_duration;
	sf::Clock ultimate_cooldown;

	int damage = 1;

	void Shoot();
public:
	bool isAttacking = false;
	Player(int x, int y, Person person, Direction direction, std::map<State, sf::Texture>& textures);
	~Player();

	void Update() override;
	void checkCollision(std::vector<Object> objects);
	void checkBulletCollision(std::vector<Object> objects, GameObject* obj);
	void checkCollisionConsumable(std::vector<Consumable*> consumable);
	void initBullets();

	std::deque<Bullet*> getBullets();

	void setState(State state);
	void setVisible(bool v);

	Person getPerson();
	bool getVisible();
};
