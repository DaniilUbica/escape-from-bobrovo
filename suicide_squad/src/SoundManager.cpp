#include "../include/Sound/SoundManager.h"

void SoundManager::Shoot(sf::SoundBuffer* s) {
	sound.setBuffer(*s);
	sound.play();
}

void SoundManager::Ult(sf::SoundBuffer* s) {
	sound.setBuffer(*s);
	sound.play();
}
