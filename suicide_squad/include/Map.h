#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <vector>

#include "Globals.h"
#include "MapObject.h"
#include "EnemiesManager.h"

class Map {
private:
	std::vector<Object> objects;
	std::map<char, sf::Texture> tiles_textures;
	std::map<char, sf::Vector2i> tiles_textures_coords;
	std::map<char, Type> tiles_types;
	int map_index = 0;

	std::string maps[MAPS_AMOUNT][MAP_WIDTH] = {
		{
	"FFFFFFFFFFFFFFFFFFFFWFFFFFFFFFFFFFFFFFFF",
	"F        F                             F",
	"F        F                             F",
	"F        F                             F",
	"F        F                    FFFFFFFFFF",
	"F        F                    F        F",
	"F       FF                    F        W",
	"F      F                               W",
	"F      F                               F",
	"F               T                      F",
	"FFFF                          FFFFFFFFFF",
	"F                                      F",
	"F                                      F",
	"F                                      F",
	"F                          FFFFFFFFFF  F",
	"FFFFFFFF                               F",
	"F      F                               F",
	"F      F                               F",
	"F      F       F     F                 F",
	"F              F     F                 F",
	"F              F     F                 F",
	"FFFFFFWWWWWFFFFFFFFFFFFFFFFFFFFFFFFFFFFF",
	},
	{
	"FFFFFFFFFFFFFFFFFFFFWFFFFFFFFFFFFFFFFFFF",
	"F                                      F",
	"F                                      F",
	"F                                      F",
	"F                             FFFFFFFFFF",
	"F                             F        F",
	"F                             F        W",
	"F                                      W",
	"F                                      F",
	"F               T                      F",
	"FFFF                          FFFFFFFFFF",
	"F                                      F",
	"F                                      F",
	"F                                      F",
	"F                          FFFFFFFFFF  F",
	"FFFF                                   F",
	"F      F                               F",
	"F      F                               F",
	"F      F       F     F                 F",
	"F              F     F                 F",
	"F              F     F                 F",
	"FFFFFFWWWWWFFFFFFFFFFFFFFFFFFFFFFFFFFFFF",
	},
	{
	"FFFFFFFFFFFFFFFFFFFFWFFFFFFFFFFFFFFFFFFF",
	"F                                      F",
	"F                                      F",
	"F                                      F",
	"F                             FFFFFFFFFF",
	"F                             F        F",
	"F                             F        W",
	"F                                      W",
	"F                                      F",
	"F               T                      F",
	"FFFF                                   F",
	"F                                      F",
	"F                                      F",
	"F                                      F",
	"F                          FFFFFFFFFF  F",
	"FFFF                                   F",
	"F      F                               F",
	"F      F                               F",
	"F      F       F     F                 F",
	"F                                      F",
	"F              F     F                 F",
	"FFFFFFWWWWWFFFFFFFFFFFFFFFFFFFFFFFFFFFFF",
	}
	};

	void fillMap();
	void fillObjects();
	void fillTexturesCoords();
	void fillObjectTypes();
public:
	void changeMap();
	void setMap(sf::Texture& range_enemy_texture, sf::Texture& melee_enemy_texture);
	void drawMap(sf::RenderWindow& window);

	std::vector<Object> getObjects();
	int getIndex();
};

