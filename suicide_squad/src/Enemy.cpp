#include "../include/Enemy.h"

void Enemy::Shoot() {
	if (bullets.back()->getPosition().x == -10 && bullets.back()->getPosition().y == 10) {
		bullets.back()->Launch();
		bullets.back()->setPosition(coordX + width / 2, coordY + height / 2);
		bullets.back()->setDirection(direction);
		bullets.pop();
	}
}

Enemy::Enemy(int x, int y, Direction direction, std::map<State, sf::Texture>& textures) {
	bullets.setSize(BULLETS_AMOUNT);
	initBullets();

	health = 3;

	coordX = x;
	coordY = y;

	width = 28;
	height = 48;

	right_border.setPosition(coordX + width + field_of_view_size, coordY - height/2);
	left_border.setPosition(coordX - field_of_view_size, coordY - height / 2);
	top_border.setPosition(coordX - width, coordY - field_of_view_size);
	down_border.setPosition(coordX - width, coordY + height + field_of_view_size);

	right_border.setSize(sf::Vector2f(2.0, 100.0));
	left_border.setSize(sf::Vector2f(2.0, 100.0));
	top_border.setSize(sf::Vector2f(100.0, 2.0));
	down_border.setSize(sf::Vector2f(100.0, 2.0));

	right_border.setFillColor(sf::Color::Blue);
	left_border.setFillColor(sf::Color::Blue);
	top_border.setFillColor(sf::Color::Blue);
	down_border.setFillColor(sf::Color::Blue);

	this->direction = direction;
	state = STAY;

	idle_animation = new Animation(textures[STAY], 0, 0, 22, 48, 4, 0.02, 22);

	sprite = idle_animation->Tick(false);

	sprite.setPosition(coordX, coordY);
}

Enemy::~Enemy() {
	delete idle_animation;
}

void Enemy::Update() {

	if (direction == RIGHT && state == STAY) {
		sprite = idle_animation->Tick(false);
	}
	if (direction == LEFT && state == STAY) {
		sprite = idle_animation->Tick(true);
	}

	if (player->getSprite().getGlobalBounds().intersects(top_border.getGlobalBounds()) && canShoot) {
		direction = UP;
		Shoot();
		canShoot = false;
	}

	if (player->getSprite().getGlobalBounds().intersects(down_border.getGlobalBounds()) && canShoot) {
		direction = DOWN;
		Shoot();
		canShoot = false;
	}

	if (player->getSprite().getGlobalBounds().intersects(left_border.getGlobalBounds()) && canShoot) {
		direction = LEFT;
		Shoot();
		canShoot = false;
	}

	if (player->getSprite().getGlobalBounds().intersects(right_border.getGlobalBounds()) && canShoot) {
		direction = RIGHT;
		Shoot();
		canShoot = false;
	}

	for (int i = 0; i < BULLETS_AMOUNT; i++) {
		bullets.elems[i]->Update();
	}

	sf::Time time;
	time = clock.getElapsedTime();
	if (time.asSeconds() >= 0.5) {
		clock.restart();
		canShoot = true;
	}

	sprite.setPosition(coordX, coordY);
}

void Enemy::takePlayer(Player* p) {
	player = p;
}

void Enemy::initBullets() {
	for (int i = 0; i < BULLETS_AMOUNT; i++) {
		bullets.push(new Bullet(-10, 10));
	}
}

std::deque<Bullet*> Enemy::getBullets() {
	return bullets.elems;
}
