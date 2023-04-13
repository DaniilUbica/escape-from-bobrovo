#pragma once

#include <SFML/Graphics.hpp>

sf::Texture heart_texture;
sf::Texture turret_texture;
sf::Texture bullet_texture;

void setTextures() {
    heart_texture.loadFromFile("assets/heart.png");

    turret_texture.loadFromFile("assets/Turret.png");

    bullet_texture.loadFromFile("assets/Bullet.png");
}