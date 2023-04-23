#pragma once

#include <SFML/Graphics.hpp>

#include "Animation.h"
#include "MapObject.h"
#include "SoundManager.h"

enum Direction {
	LEFT,
	RIGHT,
	UP,
	DOWN,
	TOP_LEFT,
	TOP_RIGHT,
	BOT_LEFT,
	BOT_RIGHT,
	NONE,
};

enum State {
	RUN,
	STAY,
	ATTACK,
	CLOSE,
	OPEN,
};

class GameObject {
protected:
	int health;
	float coordX, coordY, width, height;
	float angle = 0;
	sf::Sprite sprite;
	Direction direction;
	Animation* idle_animation;
	Animation* run_animation;
	Animation* attack_animation;
public:
	virtual void Update() = 0;
	virtual void takeDamage(int damage);

	Direction getDirection();
	sf::Sprite getSprite();
	sf::Vector2f getPosition();
	sf::Vector2f getSize();
	int getHP();
	float getAngle();

	void setDirection(Direction direction);
	void setPosition(int coordX, int coordY);
	void setAngle(float angle);
};

