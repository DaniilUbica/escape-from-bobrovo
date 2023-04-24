#pragma once

#include <SFML/Graphics.hpp>

#include "Enemy.h"

class Boss : public Enemy {
private:
	cique<Bullet*> bullets;

	void Shoot();
	void Hit();
	void initBullets();
	float player_shoot_x;
	float player_shoot_y;
public:
	ViewBorder* hit_borders;

	Boss(int x, int y, Direction direction, std::map<State, sf::Texture>& textures, int health);
	Boss(int x, int y, Direction direction, sf::Texture& texture, int health);

	~Boss();

	void checkBulletsCollision(std::vector<Object> objects);
	void Update() override;
	void checkCollision(std::vector<Object> objects);
	void lookForPlayer(float speed);

	void setBulletsTextures(sf::Texture* textures);

	std::deque<Bullet*> getBullets();
};