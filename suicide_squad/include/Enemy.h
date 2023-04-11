#pragma once

#include <SFML/Graphics.hpp>
#include <map>

#include "GameObject.h"
#include "Globals.h"
#include "Map.h"
#include "Bullet.h"
#include "Player.h"
#include "CircleBuffer.hpp"

class Enemy : public GameObject {
private:
	State state;
	Player* player;
	bool canShoot = false;
	cique<Bullet*> bullets;
	sf::Clock clock;

	const float field_of_view_size = 50.0;


	void Shoot();
public:
	sf::RectangleShape top_border;
	sf::RectangleShape down_border;
	sf::RectangleShape left_border;
	sf::RectangleShape right_border;
	Enemy(int x, int y, Direction direction, std::map<State, sf::Texture>& textures);
	~Enemy();

	void Update() override;
	void takePlayer(Player* player);
	void initBullets();
	void checkBulletsCollision(std::vector<Object> objects);

	std::deque<Bullet*> getBullets();
};

