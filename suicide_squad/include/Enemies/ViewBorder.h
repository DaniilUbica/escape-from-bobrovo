#pragma once

#include <SFML/Graphics.hpp>

#include "../Player.h"

struct ViewBorder {
	sf::RectangleShape top_border;
	sf::RectangleShape down_border;
	sf::RectangleShape left_border;
	sf::RectangleShape right_border;

	ViewBorder(int coordX, int coordY, int width, int height, float border_width, float border_height, float range);

	void Update(int coordX, int coordY, int width, int height, float range);
	Direction getDirection(int coordX, int coordY, int width, int height, Player* player);
	bool isIntersects(Player* player);
};

