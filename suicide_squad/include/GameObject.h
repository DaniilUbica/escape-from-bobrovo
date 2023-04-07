#pragma once

#include <SFML/Graphics.hpp>

#include "Animation.h"
#include "Map.h"

enum Direction {
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class GameObject {
protected:
	float coordX, coordY, width, height;
	sf::Sprite sprite;
	Direction direction;
	Animation* idle_animation;
	Animation* run_animation;
	Animation* attack_animation;
public:
	virtual void Update() = 0;

	Direction getDirection();
	sf::Sprite getSprite();
	sf::Vector2f getPosition();
	sf::Vector2f getSize();

	void setDirection(Direction direction);
};

