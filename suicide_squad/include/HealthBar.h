#pragma once

#include <SFML/Graphics.hpp>

class HealthBar {
private:
	sf::RectangleShape rect;
	int hp;
	float frame_size;
	const float BAR_HEIGHT = 5.0;
public:
	HealthBar(float coordX, float coordY, int hp, int width);

	void Update(float coordX, float coordY, int hp);

	sf::RectangleShape getRect();
};