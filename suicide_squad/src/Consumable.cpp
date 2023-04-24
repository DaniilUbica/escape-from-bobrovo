#include "../include/Features/Consumable.h"

Consumable::Consumable(ConsType type, int x, int y, sf::Texture& texture) {
	coordX = x;
	coordY = y;
	this->type = type;

	top_border = coordY - 5.0;
	bot_border = coordY + 5.0;

	sprite.setTexture(texture);

	if (type == DAMAGE) {
		sprite.setScale(0.05, 0.05);
	}

	if (type == HEALTH) {
		sprite.setScale(0.25, 0.25);
	}

	sprite.setPosition(coordX, coordY);
}

void Consumable::Update() {
	if (goTop) {
		if (coordY > top_border) {
			coordY -= CONSUMABLES_SPEED;
		}
		if (coordY < top_border) {
			coordY += CONSUMABLES_SPEED;
		}
		if (int(coordY) == int(top_border)) {
			goBot = true;
			goTop = false;
		}
	}
	if (goBot) {
		if (coordY > bot_border) {
			coordY -= CONSUMABLES_SPEED;
		}
		if (coordY < bot_border) {
			coordY += CONSUMABLES_SPEED;
		}
		if (int(coordY) == int(bot_border)) {
			goTop = true;
			goBot = false;
		}
	}

	sprite.setPosition(coordX, coordY);
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

void Consumable::setUsed(bool u) {
	isUsed = u;
}
