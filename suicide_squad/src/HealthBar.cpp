#include "../include/HealthBar.h"

HealthBar::HealthBar(float coordX, float coordY, int hp, int width) {
	this->hp = hp;
	rect.setPosition(coordX, coordY - 5.0);
	rect.setSize(sf::Vector2f(width, BAR_HEIGHT));
	rect.setFillColor(sf::Color::Green);

	frame_size = width / hp;
}

void HealthBar::Update(float coordX, float coordY, int hp) {
	rect.setPosition(coordX - 3.0, coordY - 10.0);
	if (hp < 0) {
		hp = 0;
	}
	if (rect.getSize().x > 0) {
		rect.setSize(sf::Vector2f(frame_size * hp, BAR_HEIGHT));
	}
}

sf::RectangleShape HealthBar::getRect() {
	return rect;
}
