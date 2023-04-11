#pragma once

#include <SFML/Graphics.hpp>

#include "Animation.h"
#include "Map.h"

enum Direction {
	LEFT,
	RIGHT,
	UP,
	DOWN,
	TOP_LEFT,
	TOP_RIGHT,
	BOT_LEFT,
	BOT_RIGHT,
};

enum State {
	RUN,
	STAY,
	ATTACK,
};

class GameObject {
protected:
	int health;
	float coordX, coordY, width, height;
	sf::Sprite sprite;
	Direction direction;
	Animation* idle_animation;
	Animation* run_animation;
	Animation* attack_animation;
public:
	virtual void Update() = 0;
	void takeDamage();

	Direction getDirection();
	sf::Sprite getSprite();
	sf::Vector2f getPosition();
	sf::Vector2f getSize();
	int getHP();

	void setDirection(Direction direction);
	void setPosition(int coordX, int coordY);
};

