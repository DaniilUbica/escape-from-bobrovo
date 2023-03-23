#include <iostream>
#include <SFML/Graphics.hpp>
#include <map>

#include "include/Player.h"
#include "include/Map.h"

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
        player->setState(JUMP);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        player->setState(ATTACK);
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SS!");

    std::map<State, sf::Texture> player_textures;

    Map m;
    m.setMap();


    player_textures[STAY].loadFromFile("assets/character/Idle.png");
    player_textures[RUN].loadFromFile("assets/character/Walk.png");
    player_textures[ATTACK].loadFromFile("assets/character/Attack.png");
    
    Player* player = new Player(250, 200, RIGHT, player_textures);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        controllPlayer(player);
        player->checkCollision(m.getObjects());
        player->Update();

        window.clear(sf::Color::White);
        m.drawMap(window);
        window.draw(player->getSprite());
        window.display();
    }
    delete player;
    return 0;
}