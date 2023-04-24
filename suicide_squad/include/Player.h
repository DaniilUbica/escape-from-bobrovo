#pragma once

#include <SFML/Graphics.hpp>
#include <map>

#include "Engine/GameObject.h"
#include "Engine/Globals.h"
#include "Engine/MapObject.h"
#include "Bullet.h"
#include "Engine/CircleBuffer.hpp"
#include "Features/Consumable.h"
#include "UI/Timer.h"

enum Person {
	VOLKOV,
	FEDARKOV,
	ROMKA,
};

class Player : public GameObject {
private:
	Person person;
	State state;
	Direction s_direction;

	bool canShoot = true;
	bool canTakeDamage = true;
	bool canTakeDamageFromTrap = true;
	bool isVisible = true;
	bool canUseUltimate = false;
	bool isUltimateWorking = false;

	float nx, ny;

	cique<Bullet*> bullets;
	sf::Clock clock;
	sf::Clock buffs_clock;
	sf::Clock ultimate_duration;
	sf::Clock ultimate_cooldown;
	sf::Clock damage_clock;

	sf::RenderWindow window;

	Timer* ult_timer;

	int damage = 1;
	int maps_passed = 0;

	SoundManager s_manager;

	sf::SoundBuffer* attack_sound, *ult_sound;

	void Shoot();
	void controllUltimate();
public:
	bool isAttacking = false;
	Player(int x, int y, Person person, Direction direction, std::map<State, sf::Texture>& textures, sf::Texture& ult_texture);
	~Player();

	void Update() override;
	void checkCollision(std::vector<Object> objects);
	void checkBulletCollision(std::vector<Object> objects, GameObject* obj);
	void checkBulletCollision(Bullet* obj);
	void checkCollisionConsumable(std::vector<Consumable*> consumable);
	void initBullets();
	void useUltimate();
	void countAngle(sf::RenderWindow& window);
	void countNxNy(sf::RenderWindow& window);
	void setSounds(sf::SoundBuffer& attack, sf::SoundBuffer& ult);
	void checkDamaged();
	void takeDamage(int damage) override;

	std::deque<Bullet*> getBullets();

	void setState(State state);
	void setVisible(bool v);
	void setSDirection(Direction d);
	void incMaps();

	Person getPerson();
	bool getVisible();
	Timer getUltTimer();
	int getMapsPassed();
};
