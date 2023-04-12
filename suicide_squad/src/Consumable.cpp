#include "../include/Consumable.h"

Consumable::Consumable(ConsType type, int x, int y, sf::Texture& texture) {
	coordX = x;
	coordY = y;
	this->type = type;

	sprite.setTexture(texture);
	sprite.setScale(0.01, 0.01);
	sprite.setPosition(coordX, coordY);
}

void Consumable::Update() {

}

void Consumable::Destroy() {
	isUsed = true;
}

ConsType Consumable::getType() {
	return type;
}

bool Consumable::getUsed() {
	return isUsed;
}
