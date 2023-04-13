#include <iostream>
#include <SFML/Graphics.hpp>
#include <map>

#include "include/Player.h"
#include "include/Map.h"
#include "include/Bullet.h"
#include "include/Turret.h"
#include "include/Enemy.h"
#include "include/ViewBorder.h"
#include "include/Consumable.h"
#include "include/Textures.h"

const int CONSUMABLES_AMOUNT = 2;

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

    sf::Sprite heart_sprites[PLAYER_MAX_HP];

    setTextures();

    for (int i = 0; i < PLAYER_MAX_HP; i++) {
        heart_sprites[i].setTexture(heart_texture);
        heart_sprites[i].setScale(0.01, 0.01);
    }

    Map m;
    m.setMap();

    Player* player = new Player(300, 250, VOLKOV, RIGHT, player_textures);

    Enemy* enemy = new Enemy(100, 200, RIGHT, player_textures);

    Turret* turret = new Turret(300, 100, turret_texture);

    std::vector<Consumable*> consumables;
    consumables.push_back(new Consumable(DAMAGE, 600, 300, double_damage_texture));
    consumables.push_back(new Consumable(HEALTH, 550, 40, heal_texture));

    enemy->setPatrolPoints(150, 300, 50, 100);

    auto bullets = player->getBullets();
    
    auto e_bullets = enemy->getBullets();

    auto t_bullets1 = turret->getBullets1();
    auto t_bullets2 = turret->getBullets2();
    auto t_bullets3 = turret->getBullets3();
    auto t_bullets4 = turret->getBullets4();

    for (int i = 0; i < BULLETS_AMOUNT; i++) {
        bullets[i]->setTexture(bullet_texture);

        e_bullets[i]->setTexture(bullet_texture);

        t_bullets1[i]->setTexture(bullet_texture);
        t_bullets2[i]->setTexture(bullet_texture);
        t_bullets3[i]->setTexture(bullet_texture);
        t_bullets4[i]->setTexture(bullet_texture);
    }

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
            player->Update();
            player->checkCollision(m.getObjects());
        }

        player->checkBulletCollision(m.getObjects(), enemy);
        player->checkCollisionConsumable(consumables);

        enemy->takePlayer(player);
        enemy->Update();
        enemy->checkBulletsCollision(m.getObjects());
        enemy->checkCollision(m.getObjects());

        turret->Update(m.getObjects(), player);

        m.drawMap(window);

        for (Consumable* c : consumables) {
            if (!c->getUsed()) {
                c->Update();
                window.draw(c->getSprite());
            }
        }

        for (int i = 0; i < BULLETS_AMOUNT; i++) {
            window.draw(bullets[i]->getSprite());

            window.draw(e_bullets[i]->getSprite());

            window.draw(t_bullets1[i]->getSprite());
            window.draw(t_bullets2[i]->getSprite());
            window.draw(t_bullets3[i]->getSprite());
            window.draw(t_bullets4[i]->getSprite());

            //window.draw(enemy->shoot_borders->down_border);
            //window.draw(enemy->shoot_borders->top_border);
            //window.draw(enemy->shoot_borders->right_border);
            //window.draw(enemy->shoot_borders->left_border);

            //window.draw(enemy->view_borders->down_border);
            //window.draw(enemy->view_borders->top_border);
            //window.draw(enemy->view_borders->right_border);
            //window.draw(enemy->view_borders->left_border);
        }

        window.draw(enemy->getSprite());
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
    delete enemy;
    for (Consumable* c : consumables) {
        delete c;
    }

    return 0;
}