#include "..\include\Bullet.h"

Bullet::Bullet(GameObject* obj, sf::Texture& texture) {
	this->direction = obj->getDirection();
	sprite.setTexture(texture);

	coordX = obj->getPosition().x;
	coordY = obj->getPosition().y;
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

Bullet::Bullet(GameObject* obj, float angle) {
	coordX = obj->getPosition().x;
	coordY = obj->getPosition().y;
	this->sprite.setPosition(coordX, coordY);
	sprite.setRotation(angle);
	this->angle = angle;
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
			sprite.setRotation(0);
		}
		if (direction == RIGHT) {
			coordX += BULLET_SPEED;
			sprite.setRotation(180);
		}
		if (direction == UP) {
			coordY -= BULLET_SPEED;
			sprite.setRotation(90);
		}
		if (direction == DOWN) {
			coordY += BULLET_SPEED;
			sprite.setRotation(270);
		}
		if (direction == TOP_LEFT) {
			coordX -= BULLET_SPEED;
			coordY -= BULLET_SPEED;
			sprite.setRotation(45);
		}
		if (direction == TOP_RIGHT) {
			coordX += BULLET_SPEED;
			coordY -= BULLET_SPEED;
			sprite.setRotation(135);
		}
		if (direction == BOT_LEFT) {
			coordX -= BULLET_SPEED;
			coordY += BULLET_SPEED;
			sprite.setRotation(315);
		}
		if (direction == BOT_RIGHT) {
			coordX += BULLET_SPEED;
			coordY += BULLET_SPEED;
			sprite.setRotation(225);
		}
	}

	sf::FloatRect rect = sprite.getGlobalBounds();

	if (isLaunchedByPlayer) {
		if (abs(start_x - coordX) >= BULLET_DISTANCE || abs(start_y - coordY) >= BULLET_DISTANCE) {
			this->Destroy();
		}
	}

	sprite.setOrigin(rect.left + rect.width / 2, rect.top + rect.height / 2);
	sprite.setScale(0.013, 0.013);
	sprite.setPosition(coordX, coordY);
}

void Bullet::Update(float angle) {
	sf::FloatRect rect = sprite.getGlobalBounds();
	if (isLaunched) {
		coordX += nx;
		coordY += ny;
		sprite.setRotation(this->angle);
	}

	if (isLaunchedByPlayer) {
		if (abs(start_x - coordX) >= BULLET_DISTANCE || abs(start_y - coordY) >= BULLET_DISTANCE) {
			this->Destroy();
		}
	}

	sprite.setOrigin(rect.left + rect.width / 2, rect.top + rect.height / 2);
	sprite.setScale(0.013, 0.013);
	sprite.setPosition(coordX, coordY);
}

void Bullet::checkCollision(std::vector<Object> obj) {
	for (Object o : obj) {
		if (sprite.getGlobalBounds().intersects(o.r.getGlobalBounds())) {
			if (o.type == SOLID) {
				this->Destroy();
			}
		}
	}
}

void Bullet::checkCollision(GameObject* obj) {
	if (sprite.getGlobalBounds().intersects(obj->getSprite().getGlobalBounds())) {
		obj->takeDamage(1);
		this->Destroy();
	}
}

void Bullet::checkCollision(GameObject* obj, int damage) {
	if (sprite.getGlobalBounds().intersects(obj->getSprite().getGlobalBounds())) {
		obj->takeDamage(damage);
		this->Destroy();
	}
}

void Bullet::setTexture(sf::Texture& texture) {
	sprite.setTexture(texture);
}

void Bullet::setStartPoint(float x, float y) {
	start_x = x;
	start_y = y;
}

void Bullet::setNxNy(float nx, float ny) {
	this->nx = nx;
	this->ny = ny;
}

void Bullet::setIsLaunchedByPlayer(bool a) {
	isLaunchedByPlayer = a;
}
