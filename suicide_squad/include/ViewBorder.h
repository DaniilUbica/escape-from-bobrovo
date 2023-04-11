#pragma once

#include <SFML/Graphics.hpp>

#include "GameObject.h"
#include "Player.h"

struct ViewBorder {
	const float field_of_view_size = 50.0;

	sf::RectangleShape top_border;
	sf::RectangleShape down_border;
	sf::RectangleShape left_border;
	sf::RectangleShape right_border;

	ViewBorder(int coordX, int coordY, int width, int height);

	void Update(int coordX, int coordY, int width, int height);
	Direction getDirection(int coordX, int coordY, int width, int height, Player* player);
	bool isIntersects(Player* player);
};

