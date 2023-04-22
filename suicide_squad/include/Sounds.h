#pragma once

#include <SFML/Audio.hpp>

sf::SoundBuffer revo_shot;

void setSounds() {
	revo_shot.loadFromFile("sounds/revo_shot.wav");
}