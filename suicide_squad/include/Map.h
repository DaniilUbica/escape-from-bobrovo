#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <vector>

#include "Globals.h"

enum Type {
	SOLID,
	TRAP,
	SPRITE,
};

struct Object {
	Type type;
	char ch;
	sf::RectangleShape r;
};

class Map {
private:
	std::vector<Object> objects;
	std::map<char, sf::Texture> tiles_textures;
	std::map<char, sf::Vector2i> tiles_textures_coords;
	std::map<char, Type> tiles_types;
	std::string map[MAP_HEIGHT] = {
	"FFFFFFFFFFFFFFFFFFFFWF",
	"F                    F",
	"F              FF    F",
	"F                    F",
	"F                    F",
	"F                    F",
	"F       FF           W",
	"F      F         T   W",
	"F      F             F",
	"F               T    F",
	"F                    F",
	"FFFFFFWWWWWFFFFFFFFFFF",
	};

	void fillMap();
	void fillObjects();
	void fillTexturesCoords();
	void fillObjectTypes();
public:
	void setMap();
	void drawMap(sf::RenderWindow& window);

	std::vector<Object> getObjects();
};

