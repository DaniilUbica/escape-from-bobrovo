#include <iostream>
#include <SFML/Graphics.hpp>
#include <map>

#include "include/Player.h"
#include "include/Map.h"
#include "include/Bullet.h"
#include "include/Turret.h"
#include "include/EnemiesManager.h"
#include "include/ViewBorder.h"
#include "include/Consumable.h"
#include "include/Textures.h"

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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        player->setState(ATTACK);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
        player->useUltimate();
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

    Player* player = new Player(640, 608, VOLKOV, RIGHT, player_textures, volkov_ult_texture);

    EnemiesManager e_manager;

    e_manager.addEnemy(RANGE, 100, 200, RIGHT, range_enemy_texture, 3, 150, 300, 50, 100);
    e_manager.addEnemy(RANGE, 1000, 500, RIGHT, range_enemy_texture, 3, 1100, 500, 850, 600);
    e_manager.addEnemy(RANGE, 100, 600, RIGHT, range_enemy_texture, 3, 50, 630, 250, 630);
    e_manager.addEnemy(MELEE, 600, 300, RIGHT, melee_enemy_texture, 5, 600, 300, 450, 200);
    e_manager.addEnemy(MELEE, 1200, 224, RIGHT, melee_enemy_texture, 5, 1050, 282, 1200, 200);

    Turret* turret = new Turret(500, 100, turret_texture);

    std::vector<Consumable*> consumables;
    consumables.push_back(new Consumable(DAMAGE, 600, 300, double_damage_texture));
    consumables.push_back(new Consumable(HEALTH, 550, 40, heal_texture));

    auto bullets = player->getBullets();

    auto t_bullets1 = turret->getBullets1();
    auto t_bullets2 = turret->getBullets2();
    auto t_bullets3 = turret->getBullets3();
    auto t_bullets4 = turret->getBullets4();

    e_manager.setBulletsTextures(bullet_texture);

    for (int i = 0; i < BULLETS_AMOUNT; i++) {
        bullets[i]->setTexture(bullet_texture);

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

        for (Enemy* e : e_manager.getMeleeEnemies()) {
            player->checkBulletCollision(m.getObjects(), e);
        }
        for (Enemy* e : e_manager.getRangeEnemies()) {
            player->checkBulletCollision(m.getObjects(), e);
        }

        player->checkCollisionConsumable(consumables);

        e_manager.UpdateEnemies(player);
        e_manager.checkCollision(m.getObjects());

        turret->Update(m.getObjects(), player);

        m.drawMap(window);

        if (!player->getVisible()) {
            m.changeMap();
            m.setMap();
        }

        for (Consumable* c : consumables) {
            if (!c->getUsed()) {
                c->Update();
                window.draw(c->getSprite());
            }
        }

        for (int i = 0; i < BULLETS_AMOUNT; i++) {
            window.draw(bullets[i]->getSprite());

            window.draw(t_bullets1[i]->getSprite());
            window.draw(t_bullets2[i]->getSprite());
            window.draw(t_bullets3[i]->getSprite());
            window.draw(t_bullets4[i]->getSprite());

            //window.draw(r_enemy1->attack_borders->down_border);
            //window.draw(r_enemy1->attack_borders->top_border);
            //window.draw(r_enemy1->attack_borders->right_border);
            //window.draw(r_enemy1->attack_borders->left_border);

            //window.draw(r_enemy1->view_borders->down_border);
            //window.draw(r_enemy1->view_borders->top_border);
            //window.draw(r_enemy1->view_borders->right_border);
            //window.draw(r_enemy1->view_borders->left_border);

        }

        e_manager.drawEnemies(window);

        window.draw(turret->getSprite());
        window.draw(player->getSprite());

        window.draw(player->getUltTimer().getSprite());
        window.draw(player->getUltTimer().getRect());

        for (int i = 0; i < player->getHP(); i++) {
            heart_sprites[i].setPosition(10 + 15 * i, 5);
            window.draw(heart_sprites[i]);
        }

        window.display();
    }

    delete player;
    delete turret;
    for (Consumable* c : consumables) {
        delete c;
    }

    return 0;
}