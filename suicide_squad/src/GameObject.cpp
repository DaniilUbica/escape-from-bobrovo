#include "../include/GameObject.h"

Direction GameObject::getDirection() {
    return direction;
}

sf::Sprite GameObject::getSprite() {
    return sprite;
}

sf::Vector2f GameObject::getPosition() {
    return sf::Vector2f(coordX, coordY);
}

sf::Vector2f GameObject::getSize() {
    return sf::Vector2f(width, height);
}

void GameObject::setDirection(Direction direction) {
    this->direction = direction;
}

void GameObject::setPosition(int coordX, int coordY) {
    this->coordX = coordX;
    this->coordY = coordY;
}
