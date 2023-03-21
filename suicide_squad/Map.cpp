#include "./include/Map.h"

void Map::fillMap() {
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			if (!tiles.count(map[i][j])) {
				sf::Texture tile_texture;
				tile_texture.loadFromFile("assets/Tiles.png", sf::IntRect(j* TILE_SIZE, i* TILE_SIZE, TILE_SIZE, TILE_SIZE));
				tile_texture.setRepeated(true);
				std::pair<char, sf::Texture> elem = { map[i][j], tile_texture };
				tiles.insert(elem);
			}
			else {
				continue;
			}	
		}
	}
}

void Map::fillObjects() {
	for (int i = 0; i < 3; i++) {
		int count = 0;
		int startX = 0;
		int startY = i;
		for (int j = 0; j < 10; j++) {
			char next = map[i][j + 1];
			if (map[i][j] == ' ') {
				startX = j + 1;
				continue;
			}
			if (map[i][j] != next || next == '\0') {
				count++;
				sf::RectangleShape r;
				r.setPosition(startX * TILE_SIZE, startY * TILE_SIZE);
				r.setSize(sf::Vector2f(count * TILE_SIZE, 1 * TILE_SIZE ));
				Object obj = { SOLID, map[i][j], r};
				objects.push_back(obj);
				startX = j + 1;
				count = 0;
			}
			else {
				count++;
			}
		}
	}
}

void Map::drawMap(sf::RenderWindow& window) {
	for (Object obj : objects) {
		window.draw(obj.r);
	}
}

std::vector<Object> Map::getObjects() {
	return objects;
}
