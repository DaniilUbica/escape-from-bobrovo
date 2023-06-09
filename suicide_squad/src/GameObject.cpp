#include "../include/Engine/GameObject.h"

void GameObject::takeDamage(int damage) {
    health-=damage;
    sprite.setColor(sf::Color::Red);
    sprite.setColor(sf::Color::White);
}

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

int GameObject::getHP() {
    return health;
}

float GameObject::getAngle() {
    return angle;
}

void GameObject::setDirection(Direction direction) {
    this->direction = direction;
}

void GameObject::setPosition(int coordX, int coordY) {
    this->coordX = coordX;
    this->coordY = coordY;
}

void GameObject::setAngle(float angle) {
    this->angle = angle;
}
