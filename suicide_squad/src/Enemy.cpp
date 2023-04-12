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

	borders = new ViewBorder(coordX, coordY, width, height, 2.0, 100.0);

	this->direction = direction;
	state = STAY;

	idle_animation = new Animation(textures[STAY], 0, 0, 22, 48, 4, 0.02, 22);

	sprite = idle_animation->Tick(false);

	sprite.setPosition(coordX, coordY);
}

Enemy::~Enemy() {
	delete idle_animation;
	delete borders;
}

void Enemy::Update() {

	if (health > 0) {

		if (player->getPosition().x < coordX) {
			direction = LEFT;
		}
		if (player->getPosition().x > coordX) {
			direction = RIGHT;
		}

		if ((direction == RIGHT || direction == BOT_RIGHT || direction == TOP_RIGHT) && state == STAY) {
			sprite = idle_animation->Tick(false);
		}
		if ((direction == LEFT || direction == BOT_LEFT || direction == TOP_LEFT) && state == STAY) {
			sprite = idle_animation->Tick(true);
		}

		//lookForPlayer();
		borders->Update(coordX, coordY, width, height);

		if (canShoot && borders->isIntersects(player)) {
			direction = borders->getDirection(coordX, coordY, width, height, player);
			Shoot();
			canShoot = false;
		}

		sf::Time time;
		time = clock.getElapsedTime();
		if (time.asSeconds() >= 1.0) {
			clock.restart();
			canShoot = true;
		}

		sprite.setPosition(coordX, coordY);
	}

	for (int i = 0; i < BULLETS_AMOUNT; i++) {
		bullets.elems[i]->Update();
	}
}

void Enemy::takePlayer(Player* p) {
	player = p;
}

void Enemy::initBullets() {
	for (int i = 0; i < BULLETS_AMOUNT; i++) {
		bullets.push(new Bullet(-10, 10));
	}
}

void Enemy::checkBulletsCollision(std::vector<Object> objects) {

	for (int i = 0; i < BULLETS_AMOUNT; i++) {
		bullets.elems[i]->checkCollision(player);
		bullets.elems[i]->checkCollision(objects);
	}
}

void Enemy::lookForPlayer() {
	int p_x = player->getPosition().x;
	int p_y = player->getPosition().y;

	if (!borders->isIntersects(player)) {

		if (p_x > coordX) {
			coordX += ENEMY_SPEED;
		}
		if (p_x < coordX) {
			coordX -= ENEMY_SPEED;
		}
		if (p_y > coordY) {
			coordY += ENEMY_SPEED;
		}
		if (p_y < coordY) {
			coordY -= ENEMY_SPEED;
		}
	}
}

void Enemy::Patrol(int x1, int x2, int y1, int y2) {

}

std::deque<Bullet*> Enemy::getBullets() {
	return bullets.elems;
}
