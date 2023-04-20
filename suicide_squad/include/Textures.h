#pragma once

#include <SFML/Graphics.hpp>

sf::Texture heart_texture;
sf::Texture turret_texture;
sf::Texture bullet_texture;
sf::Texture double_damage_texture;
sf::Texture heal_texture;
sf::Texture volkov_ult_texture;
sf::Texture melee_enemy_texture;
sf::Texture range_enemy_texture;

std::map<State, sf::Texture> player_textures;

std::map<State, sf::Texture> portal_textures;

void setTextures() {
    heart_texture.loadFromFile("assets/heart.png");
    
    turret_texture.loadFromFile("assets/Turret.png");
    
    bullet_texture.loadFromFile("assets/consumable/Bullet.png");

    double_damage_texture.loadFromFile("assets/consumable/double_damage.png");
    heal_texture.loadFromFile("assets/consumable/regeneration.png");

    volkov_ult_texture.loadFromFile("assets/character/volkov_ult.png");

    melee_enemy_texture.loadFromFile("assets/Knight.png");
    range_enemy_texture.loadFromFile("assets/r_enemy.png");

    player_textures[STAY].loadFromFile("assets/character/Idle4.png");
    player_textures[RUN].loadFromFile("assets/character/Walk.png");
    player_textures[ATTACK].loadFromFile("assets/character/Attack.png");

    portal_textures[STAY].loadFromFile("assets/Portal/Idle.png");
    portal_textures[OPEN].loadFromFile("assets/Portal/Open.png");
    portal_textures[CLOSE].loadFromFile("assets/Portal/Close.png");
}