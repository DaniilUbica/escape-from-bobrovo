#include "../include/Engine/Animation.h"
#include <iostream>

Animation::Animation(sf::Texture& t, int x, int y, int width, int height, int framesCount, float animSpeed, int step) {
	this->animSpeed = animSpeed;
	sprite.setTexture(t);
	currentFrame = 0;
	isPlaying = true;
	flip = false;

	for (int i = 0; i < framesCount; i++) {
		frames.push_back(sf::IntRect(x + i * step, y, width, height));
	}

	for (int i = 0; i < framesCount; i++) {
		r_frames.push_back(sf::IntRect(x + i * step+width, y, -width, height));
	}
}

sf::Sprite Animation::Tick(bool rotate) {
	currentFrame += animSpeed;

	if (currentFrame > float( frames.size()) - 0.01) {
		currentFrame -= frames.size();
	}

	int i = currentFrame;
	sprite.setTextureRect(frames[i]);

	if (!rotate) {
		sprite.setTextureRect(frames[i]);
	}
	if (rotate) {
		sprite.setTextureRect(r_frames[i]);
	}

	return sprite;
}