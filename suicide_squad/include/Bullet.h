#pragma once

#include <SFML/Graphics.hpp>

#include "GameObject.h"
#include "Globals.h"

class Bullet : public GameObject {
private:
	bool isLaunched = false;
public:
	sf::RectangleShape rect;
	Bullet(GameObject* obj, sf::Texture& texture);
	Bullet(GameObject* obj);
	Bullet(int coordX, int coordY);

	void Launch();

	void Update() override;
	void checkCollision();
};


