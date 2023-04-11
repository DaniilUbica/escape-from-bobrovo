#pragma once

#include <SFML/Graphics.hpp>

#include "GameObject.h"
#include "Globals.h"
#include "Map.h"
#include "GameObject.h"

class Bullet : public GameObject {
private:
	bool isLaunched = false;
public:
	sf::RectangleShape rect;
	Bullet(GameObject* obj, sf::Texture& texture);
	Bullet(GameObject* obj);
	Bullet(int coordX, int coordY);

	void Launch();
	void Destroy();

	void Update() override;
	void checkCollision(std::vector<Object> obj);
	void checkCollision(GameObject* obj);

	void setTexture(sf::Texture& texture);
};


