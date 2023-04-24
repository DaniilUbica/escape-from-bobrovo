#include "../include/UI/HealthBar.h"

HealthBar::HealthBar(float coordX, float coordY, int hp, int width) {
	this->hp = hp;
	health.setPosition(coordX, coordY - 5.0);
	health.setSize(sf::Vector2f(width, BAR_HEIGHT));
	health.setFillColor(sf::Color(21, 208, 30));

	background.setPosition(coordX - BACKGROUND_OFFSET, coordY - 5.0 - BACKGROUND_OFFSET);
	background.setSize(sf::Vector2f(width + BACKGROUND_OFFSET, BAR_HEIGHT + BACKGROUND_OFFSET * 2+1.0));
	background.setFillColor(sf::Color(96, 127, 97));

	frame_size = width / hp;
}

void HealthBar::Update(float coordX, float coordY, int hp) {
	health.setPosition(coordX - 3.0, coordY - 10.0);
	background.setPosition(coordX - 3.0 - BACKGROUND_OFFSET, coordY - 10.0 - BACKGROUND_OFFSET);
	if (hp < 0) {
		hp = 0;
	}
	if (health.getSize().x > 0) {
		health.setSize(sf::Vector2f(frame_size * hp, BAR_HEIGHT));
	}
}

void HealthBar::drawHealthBar(sf::RenderWindow& window) {
	window.draw(background);
	window.draw(health);
}

sf::RectangleShape HealthBar::getRect() {
	return health;
}
