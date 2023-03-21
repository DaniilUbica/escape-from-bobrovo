#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <vector>

#include "Globals.h"

enum Type {
	SOLID,
};

struct Object {
	Type type;
	char ch;
	sf::RectangleShape r;
};



class Map {
private:
	std::vector<Object> objects;
	std::map<char, sf::Texture> tiles;
	std::string map[MAP_HEIGHT] = {
	"WWWWWWWWWWWW",
	"W          W",
	"W          W",
	"W          W",
	"W          W",
	"W          W",
	"W          W",
	"W          W",
	"W          W",
	"W     S    W",
	"W          W",
	"WWWWWWWWWWWW",
	};

	void fillMap();
	void fillObjects();
public:
	void setMap();
	void drawMap(sf::RenderWindow& window);

	std::vector<Object> getObjects();
};

