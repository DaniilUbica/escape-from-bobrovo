#include "../include/Player.h"

#include <iostream>
#include <deque>

Player::Player(int x, int y, Direction direction, std::map<State, sf::Texture>& textures) {
	bullets.setSize(BULLETS_AMOUNT);
	initBullets();

	coordX = x;
	coordY = y;
	width = 28;
	height = 48;
	this->direction = direction;
	state = STAY;

	idle_animation = new Animation(textures[STAY], 0, 0, 22, 48, 4, 0.001, 22);
	run_animation = new Animation(textures[RUN], 0, 0, 26, 48, 6, 0.0013, 26);
	attack_animation = new Animation(textures[ATTACK], 0, 0, 28, 48, 5, 0.013, 28);

	sprite = idle_animation->Tick(false);
	sprite.setPosition(coordX, coordY);
}

Player::~Player() {
	delete idle_animation;
	delete run_animation;
	delete attack_animation;
	for (Bullet* b : bullets.elems) {
		delete b;
	}
}

void Player::Update() {

	if (direction == LEFT && state == RUN) {
		coordX -= PLAYER_SPEED;
		canShoot = true;
		sprite = run_animation->Tick(true);
	}

	if (direction == RIGHT && state == RUN) {
		coordX += PLAYER_SPEED;
		sprite = run_animation->Tick(false);
	}

	if (direction == UP && state == RUN) {
		coordY -= PLAYER_SPEED;
	}

	if (direction == DOWN && state == RUN) {
		coordY += PLAYER_SPEED;
	}

	if (direction == RIGHT && state == ATTACK && canShoot) {
		sprite = attack_animation->Tick(false);
		Shoot();
		canShoot = false;
	}

	if (direction == LEFT && state == ATTACK && canShoot) {
		sprite = attack_animation->Tick(true);
		Shoot();
		canShoot = false;
	}

	if (direction == RIGHT && state == STAY) {
		sprite = idle_animation->Tick(false);
	}
	if (direction == LEFT && state == STAY) {
		sprite = idle_animation->Tick(true);
	}

	for (int i = 0; i < BULLETS_AMOUNT; i++) {
		bullets.elems[i]->Update();
		
		bullets.elems[i]->checkCollision();
	}

	sprite.setPosition(coordX, coordY);
}

void Player::checkCollision(std::vector<Object> objects) {
	sf::FloatRect rect = this->sprite.getGlobalBounds();
	for (Object obj : objects) {
		if (rect.intersects(obj.r.getGlobalBounds())) {
			if (obj.type == SOLID) {
				if (direction == UP || direction == DOWN) {
					if (sprite.getPosition().y < obj.r.getPosition().y) {
						coordY = obj.r.getGlobalBounds().top - height;
					}
					if (sprite.getPosition().y > obj.r.getPosition().y) {
						coordY = obj.r.getGlobalBounds().top + obj.r.getGlobalBounds().height;
					}
				}
				if (direction == LEFT || direction == RIGHT) {
					if (sprite.getPosition().x > obj.r.getGlobalBounds().left) {
						coordX = obj.r.getGlobalBounds().left + obj.r.getGlobalBounds().width;
					}
					if (sprite.getPosition().x < obj.r.getPosition().x) {
						coordX = obj.r.getGlobalBounds().left - width;
					}
				}
			}
		}
	}
}

void Player::initBullets() {
	for (int i = 0; i < BULLETS_AMOUNT; i++) {
		bullets.push(new Bullet(-10, 10));
	}
}

std::deque<Bullet*> Player::getBullets() {
	return bullets.elems;
}

void Player::setState(State state) {
	this->state = state;
}

void Player::Shoot() {
	bullets.back()->Launch();
	bullets.back()->setPosition(coordX + width/2, coordY + height/2);
	bullets.back()->setDirection(direction);
	bullets.pop();
}
