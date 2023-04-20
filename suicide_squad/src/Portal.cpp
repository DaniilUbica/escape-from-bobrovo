#include "../include/Portal.h"

Portal::Portal(float x, float y, std::map<State, sf::Texture>& textures) {
	coordX = x;
	coordY = y;
	width = 31;
	height = 43;

	state = STAY;

	idle_animation = new Animation(textures[STAY], 0, 0, 31, 43, 7, 0.015, 64);
	open_animation = new Animation(textures[OPEN], 0, 0, 31, 43, 7, 0.015, 64);
	close_animation = new Animation(textures[CLOSE], 0, 0, 31, 43, 8, 0.015, 64);

	sprite = idle_animation->Tick(false);
	sprite.setPosition(coordX, coordY);
}

Portal::~Portal() {
	delete idle_animation;
	delete run_animation;
	delete attack_animation;
}

void Portal::Update() {
	if (state == OPEN) {
		sprite = open_animation->Tick(false);
	}
	if (state == CLOSE) {
		sprite = close_animation->Tick(false);
	}
	if (state == STAY) {
		sprite = idle_animation->Tick(false);
	}

	sprite.setPosition(coordX, coordY);
}

void Portal::takePlayer(Player* player) {
	this->player = player;
}

bool Portal::isIntersectsWithPlayer() {
	if (sprite.getGlobalBounds().intersects(player->getSprite().getGlobalBounds())) {
		state = CLOSE;
		return true;
	}
	else {
		return false;
	}
}

void Portal::setState(State st) {
	state = st;
}

State Portal::getState() {
	return state;
}
