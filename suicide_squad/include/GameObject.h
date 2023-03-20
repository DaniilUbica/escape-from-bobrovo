#pragma once

#include <SFML/Graphics.hpp>

#include "Animation.h"

enum Direction {
	LEFT,
	RIGHT,
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
};

