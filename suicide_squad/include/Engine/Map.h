#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <vector>

#include "Globals.h"
#include "MapObject.h"
#include "../Enemies/EnemiesManager.h"

class Map {
private:
	std::vector<Object> objects;
	std::map<char, sf::Texture> tiles_textures;
	std::map<char, sf::Vector2i> tiles_textures_coords;
	std::map<char, Type> tiles_types;
	int map_index = 1;
	int prev_map = 1;

	std::string maps[MAPS_AMOUNT][MAP_WIDTH] = {
		{
	"FFFFFFFFFFFFFFFFFFFFWFFFFFFFFFFFFFFFFFFF",
	"F                                      F",
	"F                                      F",
	"F FFFFFFF                              F",
	"F                                      F",
	"F                                      F",
	"F                           F          F",
	"F                           F          F",
	"F                           F          F",
	"F                           F          F",
	"F                                      F",
	"F                                      F",
	"F                                      F",
	"F                                      F",
	"F                                      F",
	"F                                      F",
	"F  FFFFFFF                FFFFFFFFF    F",
	"F                                      F",
	"F                                      F",
	"F                                      F",
	"F                                      F",
	"FFFFFFWWWWWFFFFFFFFFFFFFFFFFFFFFFFFFFFFF",
	},
	{
	"FFFFFFFFFFFFFFFFFFFFWFFFFFFFFFFFFFFFFFFF",
	"FFFFFFFFF     F         F   F          F",
	"F       F     F         F   F          F",
	"F       F     FFFFFFF  FF   F          F",
	"F       F              F    F          F",
	"F                      F    FFFFFF     F",
	"F                      F    F          F",
	"FFFFFFFFFFFFFF              F          F",
	"F                           F          F",
	"F                           F          F",
	"F                           F          F",
	"F                           F      FFFFF",
	"F                FFFFFFFFFFFF          F",
	"F                                      F",
	"F                                      F",
	"F                                      F",
	"F  FFFFFFF                FFFFFFFFF    F",
	"F                             F        F",
	"F          F                  F        F",
	"F          F                  F        F",
	"F          F                  F        F",
	"FFFFFFWWWWWFFFFFFFFFFFFFFFFFFFFFFFFFFFFF",
	},
	{
	"FFFWWWWWWFFFFFFFFFFFWFFFFFFFFFFFFFFFFFFF",
	"F                        F             F",
	"F                        F             F",
	"F       FFFFFFFFF        F             F",
	"FFFFFF                        FFFFFFFFFF",
	"F                             F        F",
	"F          FFFFF              F        W",
	"F                                      W",
	"F                                      F",
	"F               FFFFF     F            F",
	"FFFF                      F            F",
	"F                         F            F",
	"F            FFFFF        F            W",
	"F                         F            W",
	"F                         FFFFFFFFFFF  W",
	"FFFF                           F       F",
	"F      F                       F       F",
	"F      F                       F       W",
	"F      F       F     F         FFF     W",
	"F              F     F                 F",
	"F              F     F                 F",
	"FFFFFFWWWWWFFFFFFFFFFFFFFFWWWWWFFFFFFFFF",
	},
	{
	"FFFWWWWWWFFFFFFFFFFFWFFFFFFFFFFFFFFFFFFF",
	"F                        F             F",
	"F                        F             F",
	"F       FFFFFFFFF        F             F",
	"FFFFFF                        FFFFFFFFFF",
	"F                             F        F",
	"F          FFFFF              F        W",
	"F                                      W",
	"F                                      F",
	"F               FFFFF     F            F",
	"FFFF                      F            F",
	"F                         F            F",
	"F            FFFFF        F            W",
	"F                         F            W",
	"F                         FFFFFFFFFFF  W",
	"FFFF                           F       F",
	"F      F                       F       F",
	"F      F                       F       W",
	"F      F       F     F         FFF     W",
	"F              F     F                 F",
	"F              F     F                 F",
	"FFFFFFWWWWWFFFFFFFFFFFFFFFWWWWWFFFFFFFFF",
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

	void setBossMap();

	std::vector<Object> getObjects();
	int getIndex();
};

