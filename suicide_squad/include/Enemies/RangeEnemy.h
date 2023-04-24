#pragma once

#include "Enemy.h"

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