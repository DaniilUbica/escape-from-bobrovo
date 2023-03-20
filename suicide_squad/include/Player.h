#pragma once

#include <SFML/Graphics.hpp>
#include <map>

#include "GameObject.h"
#include "Globals.h"

enum State {
	RUN,
	JUMP,
	STAY,
	ATTACK,
};

class Player : public GameObject {
private:
	State state;
	bool isFalling = false;
	bool isAttacking = false;
public:
	Player(int x, int y, Direction direction, std::map<State, sf::Texture>& textures);
	~Player();
	void Update() override;

	sf::Sprite getSprite();

	void setDirection(Direction direction);
	void setState(State state);
};

