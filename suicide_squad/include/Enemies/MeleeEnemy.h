#pragma once

#include "Enemy.h"

class MeleeEnemy : public Enemy {
private:
	void Hit();
public:
	MeleeEnemy(int x, int y, Direction direction, std::map<State, sf::Texture>& textures, int health);
	MeleeEnemy(int x, int y, Direction direction, sf::Texture& texture, int health);
	void Update() override;
};