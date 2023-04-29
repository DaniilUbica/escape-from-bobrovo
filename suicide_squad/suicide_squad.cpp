#include <iostream>
#include <SFML/Graphics.hpp>
#include <map>

#include "include/Player.h"
#include "include/Engine/Map.h"
#include "include/Bullet.h"
#include "include/Enemies/Turret.h"
#include "include/Enemies/EnemiesManager.h"
#include "include/Enemies/ViewBorder.h"
#include "include/Features/Consumable.h"
#include "include/Textures.h"
#include "include/Features/Portal.h"
#include "include/Sound/Sounds.h"
#include "include/Enemies/Boss.h"

bool goToNext = false;

void controllPlayer(Player* player) {
    player->setState(STAY);
    player->setSDirection(NONE);
    player->setDirection(NONE);
    player->isAttacking = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        player->setSDirection(LEFT);
        player->setState(RUN);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        player->setSDirection(RIGHT);
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
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        player->isAttacking = true;
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
    setSounds();

    for (int i = 0; i < PLAYER_MAX_HP; i++) {
        heart_sprites[i].setTexture(heart_texture);
        heart_sprites[i].setScale(0.01, 0.01);
    }

    Map m;
    m.setMap(range_enemy_texture, melee_enemy_texture);

    Player* player = new Player(PLAYER_START_X, PLAYER_START_Y, VOLKOV, RIGHT, player_textures, volkov_ult_texture);

    EnemiesManager e_manager;

    Portal* portal = new Portal(PLAYER_START_X, PLAYER_START_Y, portal_textures);

    player->setSounds(revo_shot, volkov_ult);

    //e_manager.addEnemy(RANGE, 450, 220, RIGHT, range_enemy_texture, 3, 350, 100, 740, 300);
    //e_manager.addEnemy(RANGE, 840, 64, RIGHT, range_enemy_texture, 3, 780, 300, 860, 64);
    //e_manager.addEnemy(RANGE, 192, 650, RIGHT, range_enemy_texture, 3, 64, 600, 300, 630);
    //e_manager.addEnemy(RANGE, 400, 650, RIGHT, range_enemy_texture, 3, 450, 550, 900, 630);
    //e_manager.addEnemy(RANGE, 1000, 320, RIGHT, range_enemy_texture, 3, 1100, 280, 950, 440);
    //e_manager.addEnemy(RANGE, 1000, 64, RIGHT, range_enemy_texture, 3, 1200, 64, 950, 130);
    //e_manager.addEnemy(MELEE, 1000, 650, RIGHT, melee_enemy_texture, 5, 1070, 630, 1200, 570);
    //e_manager.addEnemy(MELEE, 400, 480, RIGHT, melee_enemy_texture, 5, 900, 490, 250, 440);
    //e_manager.addEnemy(MELEE, 640, 64, RIGHT, melee_enemy_texture, 5, 540, 64, 740, 64);
    //e_manager.addEnemy(MELEE, 450, 400, RIGHT, melee_enemy_texture, 5, 300, 350, 800, 350);
    //e_manager.addEnemy(MELEE, 350, 400, RIGHT, melee_enemy_texture, 5, 100, 350, 500, 450);

    e_manager.setSounds(revo_shot, hit);

    Turret* turret = new Turret(500, 500, turret_texture);

    std::vector<Consumable*> consumables;
    consumables.push_back(new Consumable(DAMAGE, 700, 40, double_damage_texture));
    consumables.push_back(new Consumable(HEALTH, 550, 330, heal_texture));
    consumables.push_back(new Consumable(HEALTH, 300, 550, heal_texture));
    consumables.push_back(new Consumable(HEALTH, 900, 600, heal_texture));

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
        m.drawMap(window);
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (player->getHP() > 0) {
            controllPlayer(player);
            player->countAngle(window);
            player->countNxNy(window);
            player->Update();
            player->checkCollision(m.getObjects());
        }

        if (e_manager.getBoss() != NULL) {
            player->checkBulletCollision(m.getObjects(), e_manager.getBoss());
        }

        for (MeleeEnemy* e : e_manager.getMeleeEnemies()) {
            player->checkBulletCollision(m.getObjects(), e);
        }
        for (RangeEnemy* e : e_manager.getRangeEnemies()) {
            player->checkBulletCollision(m.getObjects(), e);
        }

        portal->takePlayer(player);

        player->checkCollisionConsumable(consumables);

        e_manager.UpdateEnemies(player, m.getObjects());
        e_manager.checkCollision(m.getObjects());

        if (e_manager.getKilledEnemies() == e_manager.getEnemiesAmount()) {
            window.draw(portal->getSprite());
            portal->Update();
            portal->isIntersectsWithPlayer();
            if (int(portal->getCloseAnimation()->currentFrame) == 6) {

                portal->Restart(PLAYER_START_X, PLAYER_START_Y);
                player->setPosition(player->getPosition().x, player->getPosition().y);
                player->incMaps();
                e_manager.setKilledToNull();

                if (player->getMapsPassed() == LEVELS_BEFORE_BOSS) {
                    m.setBossMap();
                }
                else {
                    m.changeMap();
                }
                m.setMap(range_enemy_texture, melee_enemy_texture);

                for (Consumable* c : consumables) {
                    c->setUsed(false);
                }
                if (m.getIndex() == 0) {
                    e_manager.Clear();
                    consumables.clear();

                    e_manager.addEnemy(RANGE, -450, -220, RIGHT, range_enemy_texture, 3, 350, 100, 740, 300);
                    e_manager.addEnemy(RANGE, -840, -64, RIGHT, range_enemy_texture, 3, 780, 300, 860, 64);
                    e_manager.addEnemy(RANGE, -192, 650, RIGHT, range_enemy_texture, 3, 64, 600, 300, 630);
                    e_manager.addEnemy(RANGE, -400, 650, RIGHT, range_enemy_texture, 3, 450, 550, 900, 630);
                    e_manager.addEnemy(RANGE, -1000, 320, RIGHT, range_enemy_texture, 3, 1100, 280, 950, 440);
                    e_manager.addEnemy(RANGE, -1000, 64, RIGHT, range_enemy_texture, 3, 1200, 64, 950, 130);
                    e_manager.addEnemy(MELEE, -1000, 650, RIGHT, melee_enemy_texture, 5, 1070, 630, 1200, 570);
                    e_manager.addEnemy(MELEE, -400, 480, RIGHT, melee_enemy_texture, 5, 900, 490, 250, 440);
                    e_manager.addEnemy(MELEE, -640, 64, RIGHT, melee_enemy_texture, 5, 540, 64, 740, 64);
                    e_manager.addEnemy(MELEE, -450, 400, RIGHT, melee_enemy_texture, 5, 300, 350, 800, 350);
                    e_manager.addEnemy(MELEE, -350, 400, RIGHT, melee_enemy_texture, 5, 100, 350, 500, 450);
                    e_manager.addEnemy(BOSS, 500, 300, RIGHT, volkov_boss_texture, 10, 600, 300, 450, 200);
                    e_manager.getBoss()->setBulletsTextures(enemy_bullets_textures);
                }
                else if (m.getIndex() == 1) {
                    e_manager.Clear();
                    consumables.clear();
                    consumables.push_back(new Consumable(DAMAGE, 700, 40, double_damage_texture));
                    consumables.push_back(new Consumable(HEALTH, 550, 330, heal_texture));
                    consumables.push_back(new Consumable(HEALTH, 1050, 500, heal_texture));

                    e_manager.addEnemy(RANGE, 450, 220, RIGHT, range_enemy_texture, 3, 350, 100, 740, 300);
                    e_manager.addEnemy(RANGE, 840, 64, RIGHT, range_enemy_texture, 3, 780, 300, 860, 64);
                    e_manager.addEnemy(RANGE, 192, 650, RIGHT, range_enemy_texture, 3, 64, 600, 300, 630);
                    e_manager.addEnemy(RANGE, 400, 650, RIGHT, range_enemy_texture, 3, 450, 550, 900, 630);
                    e_manager.addEnemy(RANGE, 1000, 320, RIGHT, range_enemy_texture, 3, 1100, 280, 950, 440);
                    e_manager.addEnemy(RANGE, 1000, 64, RIGHT, range_enemy_texture, 3, 1200, 64, 950, 130);
                    e_manager.addEnemy(MELEE, 1000, 650, RIGHT, melee_enemy_texture, 5, 1070, 630, 1200, 570);
                    e_manager.addEnemy(MELEE, 400, 480, RIGHT, melee_enemy_texture, 5, 900, 490, 250, 440);
                    e_manager.addEnemy(MELEE, 640, 64, RIGHT, melee_enemy_texture, 5, 540, 64, 740, 64);
                    e_manager.addEnemy(MELEE, 450, 400, RIGHT, melee_enemy_texture, 5, 300, 350, 800, 350);
                    e_manager.addEnemy(MELEE, 350, 400, RIGHT, melee_enemy_texture, 5, 100, 350, 500, 450);
                }
                else if (m.getIndex() == 2) {
                    e_manager.Clear();
                    consumables.clear();
                    consumables.push_back(new Consumable(DAMAGE, 700, 40, double_damage_texture));
                    consumables.push_back(new Consumable(HEALTH, 550, 330, heal_texture));
                    consumables.push_back(new Consumable(HEALTH, 1050, 500, heal_texture));

                    e_manager.addEnemy(RANGE, 384, 192, RIGHT, range_enemy_texture, 3, 330, 160, 650, 160);
                    e_manager.addEnemy(RANGE, 672, 96, RIGHT, range_enemy_texture, 3, 650, 96, 860, 245);
                    e_manager.addEnemy(RANGE, 192, 650, RIGHT, range_enemy_texture, 3, 64, 570, 220, 630);
                    e_manager.addEnemy(RANGE, -400, 650, RIGHT, range_enemy_texture, 3, 450, 550, 900, 630);
                    e_manager.addEnemy(RANGE, -1000, 320, RIGHT, range_enemy_texture, 3, 1100, 280, 950, 440);
                    e_manager.addEnemy(RANGE, 1000, 64, RIGHT, range_enemy_texture, 3, 1200, 64, 900, 100);
                    e_manager.addEnemy(MELEE, 128, 256, RIGHT, melee_enemy_texture, 5, 200, 300, 450, 350);
                    e_manager.addEnemy(MELEE, 1000, 300, RIGHT, melee_enemy_texture, 5, 1200, 200, 900, 400);
                    e_manager.addEnemy(MELEE, -640, 64, RIGHT, melee_enemy_texture, 5, 540, 64, 740, 64);
                    e_manager.addEnemy(MELEE, 450, 500, RIGHT, melee_enemy_texture, 5, 300, 450, 800, 450);
                    e_manager.addEnemy(MELEE, 1000, 650, RIGHT, melee_enemy_texture, 5, 780, 630, 1200, 630);
                }
                else if (m.getIndex() == 3) {
                    e_manager.Clear();
                    consumables.clear();
                    consumables.push_back(new Consumable(DAMAGE, 700, 40, double_damage_texture));
                    consumables.push_back(new Consumable(HEALTH, 550, 330, heal_texture));
                    consumables.push_back(new Consumable(HEALTH, 1050, 500, heal_texture));

                    e_manager.addEnemy(RANGE, 384, 192, RIGHT, range_enemy_texture, 3, 330, 160, 650, 160);
                    e_manager.addEnemy(RANGE, 672, 96, RIGHT, range_enemy_texture, 3, 650, 96, 860, 245);
                    e_manager.addEnemy(RANGE, 192, 650, RIGHT, range_enemy_texture, 3, 64, 570, 220, 630);
                    e_manager.addEnemy(RANGE, -400, 650, RIGHT, range_enemy_texture, 3, 450, 550, 900, 630);
                    e_manager.addEnemy(RANGE, -1000, 320, RIGHT, range_enemy_texture, 3, 1100, 280, 950, 440);
                    e_manager.addEnemy(RANGE, 1000, 64, RIGHT, range_enemy_texture, 3, 1200, 64, 900, 100);
                    e_manager.addEnemy(MELEE, 128, 256, RIGHT, melee_enemy_texture, 5, 200, 300, 450, 350);
                    e_manager.addEnemy(MELEE, 1000, 300, RIGHT, melee_enemy_texture, 5, 1200, 200, 900, 400);
                    e_manager.addEnemy(MELEE, -640, 64, RIGHT, melee_enemy_texture, 5, 540, 64, 740, 64);
                    e_manager.addEnemy(MELEE, 450, 500, RIGHT, melee_enemy_texture, 5, 300, 450, 800, 450);
                    e_manager.addEnemy(MELEE, 1000, 650, RIGHT, melee_enemy_texture, 5, 780, 630, 1200, 630);
                }
                e_manager.setBulletsTextures(bullet_texture);
                e_manager.setSounds(revo_shot, hit);
            }
        }

        turret->Update(m.getObjects(), player);

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

            //window.draw(boss->view_borders->down_border);
            //window.draw(boss->view_borders->top_border);
            //window.draw(boss->view_borders->right_border);
            //window.draw(boss->view_borders->left_border);

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
    delete portal;
    for (Consumable* c : consumables) {
        delete c;
    }

    return 0;
}