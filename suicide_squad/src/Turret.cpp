#include "../include/Turret.h"

Turret::Turret(int coordX, int coordY, sf::Texture& texture) {
	bullets1.setSize(BULLETS_AMOUNT);
	bullets2.setSize(BULLETS_AMOUNT);
	bullets3.setSize(BULLETS_AMOUNT);
	bullets4.setSize(BULLETS_AMOUNT);
	initBullets();

	this->coordX = coordX;
	this->coordY = coordY;

	height = 50;
	width = 46;

	sprite.setTexture(texture);

	sprite.setPosition(coordX, coordY);
}

Turret::~Turret() {
	for (Bullet* b : bullets1.elems) {
		delete b;
	}
	for (Bullet* b : bullets2.elems) {
		delete b;
	}
	for (Bullet* b : bullets3.elems) {
		delete b;
	}
	for (Bullet* b : bullets4.elems) {
		delete b;
	}
}

void Turret::Update(std::vector<Object> objects, Player* player) {

	if (canShoot) {
		Shoot();
		canShoot = false;
	}

	for (int i = 0; i < BULLETS_AMOUNT; i++) {
		bullets1.elems[i]->Update();
		bullets2.elems[i]->Update();
		bullets3.elems[i]->Update();
		bullets4.elems[i]->Update();

		bullets1.elems[i]->checkCollision(objects);
		bullets2.elems[i]->checkCollision(objects);
		bullets3.elems[i]->checkCollision(objects);
		bullets4.elems[i]->checkCollision(objects);

		bullets1.elems[i]->checkCollision(player);
		bullets2.elems[i]->checkCollision(player);
		bullets3.elems[i]->checkCollision(player);
		bullets4.elems[i]->checkCollision(player);
	}

	sf::Time time;
	time = clock.getElapsedTime();
	if (time.asSeconds() >= 2) {
		clock.restart();
		canShoot = true;
	}
}

void Turret::Update() {

}

void Turret::initBullets() {
	for (int i = 0; i < BULLETS_AMOUNT; i++) {
		bullets1.push(new Bullet(-10, 10));
		bullets2.push(new Bullet(-10, 10));
		bullets3.push(new Bullet(-10, 10));
		bullets4.push(new Bullet(-10, 10));
	}
}

void Turret::Shoot() {
	if (bullets1.back()->getPosition().x == -10 && bullets1.back()->getPosition().y == 10) {
		bullets1.back()->Launch();
		bullets1.back()->setPosition(coordX + width / 2, coordY + height / 2);
		bullets1.back()->setDirection(UP);
		bullets1.pop();
	}
	if (bullets2.back()->getPosition().x == -10 && bullets2.back()->getPosition().y == 10) {
		bullets2.back()->Launch();
		bullets2.back()->setPosition(coordX + width / 2, coordY + height / 2);
		bullets2.back()->setDirection(DOWN);
		bullets2.pop();
	}
	if (bullets3.back()->getPosition().x == -10 && bullets3.back()->getPosition().y == 10) {
		bullets3.back()->Launch();
		bullets3.back()->setPosition(coordX + width / 2, coordY + height / 2);
		bullets3.back()->setDirection(LEFT);
		bullets3.pop();
	}
	if (bullets4.back()->getPosition().x == -10 && bullets4.back()->getPosition().y == 10) {
		bullets4.back()->Launch();
		bullets4.back()->setPosition(coordX + width / 2, coordY + height / 2);
		bullets4.back()->setDirection(RIGHT);
		bullets4.pop();
	}
}

std::deque<Bullet*> Turret::getBullets1() {
	return bullets1.elems;
}

std::deque<Bullet*> Turret::getBullets2() {
	return bullets2.elems;
}

std::deque<Bullet*> Turret::getBullets3() {
	return bullets3.elems;
}

std::deque<Bullet*> Turret::getBullets4() {
	return bullets4.elems;
}
