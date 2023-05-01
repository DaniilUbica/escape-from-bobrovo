#pragma once

#include <SFML/Graphics.hpp>

class Button {
private:
    float coordX, coordY;
    float height, width;
    sf::Text text;
    sf::RectangleShape border;
    sf::RectangleShape button;
    sf::Sprite sprite;
    sf::Vector3i border_color;
    sf::Vector3i button_color;
    sf::Vector3i text_color;

    const float BORDER_SIZE = 6.0;

    bool checkMouseInButton(sf::Vector2i coords);

public:
    Button(float x, float y, float w, float h, sf::Vector3i border_color, sf::Vector3i button_color, sf::Vector3i text_color, sf::Text text);

    void Update(sf::RenderWindow& window);

    bool checkClick(sf::RenderWindow& window, sf::Event& event);

    void drawButton(sf::RenderWindow& window);
};