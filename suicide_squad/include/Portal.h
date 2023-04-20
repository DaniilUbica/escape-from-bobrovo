#pragma once

#include <SFML/Graphics.hpp>
#include <map>

#include "Player.h"

class Portal : public GameObject {
private:
	Player* player;
	Animation* open_animation;
	Animation* close_animation;
	State state;
public:
	Portal(float x, float y, std::map<State, sf::Texture>& textures);
	~Portal();

	void Update() override;
	void takePlayer(Player* player);
	bool isIntersectsWithPlayer();
	void Restart(float x, float y);

	void setState(State st);

	State getState();
	Animation* getCloseAnimation();
};