#pragma once

#include <SFML/Audio.hpp>

class SoundManager {
private:
	sf::Music music;
	sf::Sound sound;
public:
	void Shoot(sf::SoundBuffer* s);
};

