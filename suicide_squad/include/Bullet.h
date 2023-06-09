#pragma once

#include <SFML/Graphics.hpp>

#include "Engine/GameObject.h"
#include "Engine/Globals.h"
#include "Engine/MapObject.h"

class Bullet : public GameObject {
private:
	bool isLaunched = false;
	float start_x;
	float start_y;
	float nx;
	float ny;
	bool isLaunchedByPlayer = false;
public:

	sf::RectangleShape rect;
	Bullet(GameObject* obj, sf::Texture& texture);
	Bullet(GameObject* obj);
	Bullet(GameObject* obj, float angle);
	Bullet(int coordX, int coordY);

	void Launch();
	void Destroy();

	void Update() override;
	void Update(float angle);
	void Update(GameObject* obj);
	void checkCollision(std::vector<Object> obj);
	void checkCollision(GameObject* obj);
	void checkCollision(Bullet* obj);
	void checkCollision(GameObject* obj, int damage);

	void setTexture(sf::Texture& texture);
	void setStartPoint(float x, float y);
	void setNxNy(float nx, float ny);
	void setIsLaunchedByPlayer(bool a);

};


