#include <iostream>
#include <SFML/Graphics.hpp>
#include <map>

#include "include/Player.h"
#include "include/Map.h"
#include "include/Bullet.h"
#include "include/Turret.h"

void controllPlayer(Player* player) {
    player->setState(STAY);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        player->setDirection(LEFT);
        player->setState(RUN);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        player->setDirection(RIGHT);
        player->setState(RUN);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        player->setDirection(UP);
        player->setState(RUN);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        player->setDirection(DOWN);
        player->setState(RUN);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        player->setState(ATTACK);
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SS!");

    std::map<State, sf::Texture> player_textures;

    sf::Texture heart_texture;
    heart_texture.loadFromFile("assets/heart.png");

    sf::Texture turret_texture;
    turret_texture.loadFromFile("assets/Turret.png");

    sf::Sprite heart_sprites[PLAYER_MAX_HP];

    for (int i = 0; i < PLAYER_MAX_HP; i++) {
        heart_sprites[i].setTexture(heart_texture);
        heart_sprites[i].setScale(0.01, 0.01);
    }

    Map m;
    m.setMap();

    player_textures[STAY].loadFromFile("assets/character/Idle.png");
    player_textures[RUN].loadFromFile("assets/character/Walk.png");
    player_textures[ATTACK].loadFromFile("assets/character/Attack.png");
    
    Player* player = new Player(250, 200, RIGHT, player_textures);

    Turret* turret = new Turret(150, 100, turret_texture);

    auto bullets = player->getBullets();
    
    auto t_bullets1 = turret->getBullets1();
    auto t_bullets2 = turret->getBullets2();
    auto t_bullets3 = turret->getBullets3();
    auto t_bullets4 = turret->getBullets4();

    while (window.isOpen())
    {
        window.clear(sf::Color::White);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (player->getHP() > 0) {
            controllPlayer(player);
            player->checkCollision(m.getObjects());
            player->Update();
        }

        turret->Update(m.getObjects(), player);

        m.drawMap(window);

        for (int i = 0; i < BULLETS_AMOUNT; i++) {
            window.draw(bullets[i]->rect);

            window.draw(t_bullets1[i]->rect);
            window.draw(t_bullets2[i]->rect);
            window.draw(t_bullets3[i]->rect);
            window.draw(t_bullets4[i]->rect);
        }

        window.draw(turret->getSprite());
        window.draw(player->getSprite());

        for (int i = 0; i < player->getHP(); i++) {
            heart_sprites[i].setPosition(10 + 15 * i, 5);
            window.draw(heart_sprites[i]);
        }

        window.display();
    }

    delete player;
    delete turret;

    return 0;
}