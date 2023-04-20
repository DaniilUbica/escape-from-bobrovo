#pragma once

#include <SFML/Graphics.hpp>

class HealthBar {
private:
	sf::RectangleShape health;
	sf::RectangleShape background;
	int hp;
	float frame_size;
	const float BAR_HEIGHT = 5.0;
	const float BACKGROUND_OFFSET = 2.0;
public:
	HealthBar(float coordX, float coordY, int hp, int width);

	void Update(float coordX, float coordY, int hp);
	void drawHealthBar(sf::RenderWindow& window);

	sf::RectangleShape getRect();
};