#pragma once

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