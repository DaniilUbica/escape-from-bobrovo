#pragma once

#include <SFML/Audio.hpp>

sf::SoundBuffer revo_shot;
sf::SoundBuffer hit;
sf::SoundBuffer volkov_ult;

void setSounds() {
	revo_shot.loadFromFile("sounds/revo_shot.wav");
	hit.loadFromFile("sounds/punch.wav");
	volkov_ult.loadFromFile("sounds/volkov_ult.wav");
}