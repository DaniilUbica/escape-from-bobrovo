#pragma once

#include "GameObject.h"

enum ConsType {
	DAMAGE,
	HEALTH,
};

class Consumable : public GameObject {
private:
	ConsType type;
	bool isUsed = false;
public:
	Consumable(ConsType type, int x, int y, sf::Texture& texture);

	void Update();
	void Destroy();

	ConsType getType();
	bool getUsed();
};

