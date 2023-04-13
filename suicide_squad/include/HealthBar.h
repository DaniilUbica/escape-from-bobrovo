#pragma once

#include <SFML/Graphics.hpp>

class HealthBar {
	sf::RectangleShape rect;
	sf::RectangleShape border;
	int hp;
	float frame_size;
	const float BAR_HEIGHT = 5.0;
public:
	HealthBar(float coordX, float coordY, int hp, int width);

	void Update(float coordX, float coordY, int hp);

	sf::RectangleShape getRect();
};