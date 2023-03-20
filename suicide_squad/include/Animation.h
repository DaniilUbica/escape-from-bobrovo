#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>

class Animation {
public:
	std::vector<sf::IntRect> frames, r_frames;
	float currentFrame, animSpeed;
	bool flip, isPlaying;
	sf::Sprite sprite;

	Animation() = default;

	Animation(sf::Texture& t, int x, int y, 
		int width, int height, int framesCount, float animSpeed, int step);

	sf::Sprite Tick(bool rotate);
};