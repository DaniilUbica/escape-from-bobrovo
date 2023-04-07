#include "..\include\Bullet.h"
#include <iostream>

Bullet::Bullet(GameObject* obj, sf::Texture& texture) {
	this->direction = obj->getDirection();
	sprite.setTexture(texture);

	coordX = obj->getPosition().x;
	coordY = obj->getPosition().y + obj->getSize().y / 2;
	this->sprite.setPosition(coordX, coordY);
}

void Bullet::Update() {
	if (direction == LEFT) {
		coordX -= BULLET_SPEED;
	}
	if (direction == RIGHT) {
		coordX += BULLET_SPEED;
	}
	if (direction == UP) {
		coordY -= BULLET_SPEED;
	}
	if (direction == DOWN) {
		coordY += BULLET_SPEED;
	}
	std::cout << coordX << " " << coordY << "\n";
	sprite.setScale(0.01, 0.01);
	this->sprite.setPosition(coordX, coordY);
}

void Bullet::checkCollision() {

}
