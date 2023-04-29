#include "../include/Enemies/View.h"

View::View(float range, float max_range) {
    this->range = range;
    this->max_range = max_range;
    for (int i = 0; i < ACCURACY; i++) {
        sticks[i].setSize(sf::Vector2f(2, range));
        sticks[i].setRotation(i * (360/ACCURACY));
        sticks[i].setFillColor(sf::Color::Green);
    }
}

void View::Update(float x, float y, std::vector<Object>& objects) {
    for (int i = 0; i < ACCURACY; i++) {
        for (int j = 0; j < objects.size(); j++) {

            sf::FloatRect o_rect = objects[j].r.getGlobalBounds();

            if (!sticks[i].getGlobalBounds().intersects(o_rect) && sticks[i].getSize().y < max_range && objects[j].type != SOLID) {
                sticks[i].setSize(sf::Vector2f(sticks[i].getSize().x, sticks[i].getSize().y + 0.01));
            }
            else if (sticks[i].getGlobalBounds().intersects(o_rect) && objects[j].type == SOLID && sticks[i].getSize().y > 1.0) {
                sticks[i].setSize(sf::Vector2f(sticks[i].getSize().x, sticks[i].getSize().y - 2));
            }
        }
    }

    for (int i = 0; i < ACCURACY; i++) {
        sticks[i].setPosition(x, y);
    }
}

bool View::isIntersects(Player* player) {
    for (int i = 0; i < ACCURACY; i++) {
        sf::FloatRect t = sticks[i].getGlobalBounds();
        
        if (t.intersects(player->getSprite().getGlobalBounds())) {
            return true;
        }
    }

    return false;
}

sf::RectangleShape* View::getSticks() {
    return sticks;
}
