#pragma once

#include "../Engine/GameObject.h"
#include "../Engine/Globals.h"

enum ConsType {
	DAMAGE,
	HEALTH,
};

class Consumable : public GameObject {
private:
	ConsType type;
	bool isUsed = false;
	bool goTop = true;
	bool goBot = false;
	float top_border;
	float bot_border;
public:
	Consumable(ConsType type, int x, int y, sf::Texture& texture);

	void Update();
	void Destroy();

	void setUsed(bool u);

	ConsType getType();
	bool getUsed();
};

