#include "../include/SoundManager.h"

void SoundManager::Shoot(sf::SoundBuffer* s) {
	sound.setBuffer(*s);
	sound.play();
}
