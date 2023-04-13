#pragma once

#include <SFML/Graphics.hpp>

sf::Texture heart_texture;
sf::Texture turret_texture;
sf::Texture bullet_texture;
sf::Texture double_damage_texture;
sf::Texture heal_texture;

std::map<State, sf::Texture> player_textures;

void setTextures() {
    heart_texture.loadFromFile("assets/heart.png");
    
    turret_texture.loadFromFile("assets/Turret.png");
    
    bullet_texture.loadFromFile("assets/consumable/Bullet.png");

    double_damage_texture.loadFromFile("assets/consumable/double_damage.png");
    heal_texture.loadFromFile("assets/consumable/regeneration.png");

    player_textures[STAY].loadFromFile("assets/character/Idle.png");
    player_textures[RUN].loadFromFile("assets/character/Walk.png");
    player_textures[ATTACK].loadFromFile("assets/character/Attack.png");
}