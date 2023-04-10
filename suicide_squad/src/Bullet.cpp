#include "..\include\Bullet.h"

Bullet::Bullet(GameObject* obj, sf::Texture& texture) {
	this->direction = obj->getDirection();
	sprite.setTexture(texture);

	coordX = obj->getPosition().x;
	coordY = obj->getPosition().y + obj->getSize().y / 2;
	this->sprite.setPosition(coordX, coordY);
}

Bullet::Bullet(GameObject* obj) {
	this->direction = obj->getDirection();

	coordX = obj->getPosition().x;
	coordY = obj->getPosition().y + obj->getSize().y / 2;

	rect.setPosition(coordX, coordY);
	rect.setSize(sf::Vector2f(6, 6));
	rect.setFillColor(sf::Color::Black);
}

Bullet::Bullet(int coordX, int coordY) {
	this->coordX = coordX;
	this->coordY = coordY;

	rect.setPosition(coordX, coordY);
	rect.setSize(sf::Vector2f(6, 6));
	rect.setFillColor(sf::Color::Black);
}

void Bullet::Launch() {
	isLaunched = true;
}

void Bullet::Destroy() {
	this->setPosition(-10, 10);
	isLaunched = false;
}

void Bullet::Update() {
	if (isLaunched) {
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
	}

	sprite.setScale(0.01, 0.01);
	sprite.setPosition(coordX, coordY);
	rect.setPosition(coordX, coordY);
}

void Bullet::checkCollision(std::vector<Object> obj) {
	for (Object o : obj) {
		if (rect.getGlobalBounds().intersects(o.r.getGlobalBounds())) {
			if (o.type == SOLID) {
				this->Destroy();
			}
		}
	}
}

void Bullet::checkCollision(GameObject* obj) {
	if (rect.getGlobalBounds().intersects(obj->getSprite().getGlobalBounds())) {
		obj->takeDamage();
		this->Destroy();
	}
}
