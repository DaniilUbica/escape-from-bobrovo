#include "../include/ViewBorder.h"

ViewBorder::ViewBorder(int coordX, int coordY, int width, int height, float border_width, float border_height, float range) {
		right_border.setSize(sf::Vector2f(-border_width/2, border_height));
		left_border.setSize(sf::Vector2f(border_width/2, border_height));
		top_border.setSize(sf::Vector2f(border_height, border_width/2));
		down_border.setSize(sf::Vector2f(border_height, -border_width/2));

		right_border.setFillColor(sf::Color::Blue);
		left_border.setFillColor(sf::Color::Blue);
		top_border.setFillColor(sf::Color::Blue);
		down_border.setFillColor(sf::Color::Blue);
}

void ViewBorder::Update(int coordX, int coordY, int width, int height, float range) {
	top_border.setPosition(coordX - SPRITE_SIZE/2 - range, coordY - SPRITE_SIZE / 2 - range);
	down_border.setPosition(coordX - SPRITE_SIZE / 2 - range, coordY + SPRITE_SIZE / 2 + range);
	right_border.setPosition(coordX + SPRITE_SIZE / 2 + range, coordY- SPRITE_SIZE / 2 - range);
	left_border.setPosition(coordX - SPRITE_SIZE / 2 - range, coordY- SPRITE_SIZE / 2 - range);
}

Direction ViewBorder::getDirection(int coordX, int coordY, int width, int height, Player* player) {
	Direction direction;

	if (player->getSprite().getGlobalBounds().intersects(top_border.getGlobalBounds())) {
		if (player->getSprite().getPosition().x >= coordX + width / 2) {
			direction = TOP_RIGHT;
		}
		else if (player->getSprite().getPosition().x + player->getSize().x / 2 <= coordX) {
			direction = TOP_LEFT;
		}
		else {
			direction = UP;
		}
	}

	if (player->getSprite().getGlobalBounds().intersects(down_border.getGlobalBounds())) {

		if (player->getSprite().getPosition().x >= coordX + width / 2) {
			direction = BOT_RIGHT;
		}
		else if (player->getSprite().getPosition().x + player->getSize().x / 2 <= coordX) {
			direction = BOT_LEFT;
		}
		else {
			direction = DOWN;
		}
	}

	if (player->getSprite().getGlobalBounds().intersects(right_border.getGlobalBounds())) {
		if (player->getSprite().getPosition().y + player->getSize().y <= coordY + height / 2) {
			direction = TOP_RIGHT;
		}
		else if (player->getSprite().getPosition().y >= coordY + height / 2) {
			direction = BOT_RIGHT;
		}
		else {
			direction = RIGHT;
		}
	}

	if (player->getSprite().getGlobalBounds().intersects(left_border.getGlobalBounds())) {
		if (player->getSprite().getPosition().y + player->getSize().y <= coordY + height / 2) {
			direction = TOP_LEFT;
		}
		else if (player->getSprite().getPosition().y >= coordY + height / 2) {
			direction = BOT_LEFT;
		}
		else {
			direction = LEFT;
		}
	}

	return direction;
}

bool ViewBorder::isIntersects(Player* player) {
	return player->getSprite().getGlobalBounds().intersects(left_border.getGlobalBounds()) || 
		player->getSprite().getGlobalBounds().intersects(right_border.getGlobalBounds()) ||
		player->getSprite().getGlobalBounds().intersects(down_border.getGlobalBounds()) ||
		player->getSprite().getGlobalBounds().intersects(top_border.getGlobalBounds());
}
