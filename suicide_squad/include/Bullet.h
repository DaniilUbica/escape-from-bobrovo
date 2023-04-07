#pragma once

#include <SFML/Graphics.hpp>

#include "GameObject.h"
#include "Globals.h"

class Bullet : public GameObject {
public:
	Bullet(GameObject* obj, sf::Texture& texture);

	void Update() override;
	void checkCollision();
};


