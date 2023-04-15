#include <iostream>
#include <deque>

#include "../include/Player.h"

Player::Player(int x, int y, Person person, Direction direction, std::map<State, sf::Texture>& textures, sf::Texture& ult_texture) {
	bullets.setSize(BULLETS_AMOUNT);
	initBullets();

	health = 5;
	coordX = x;
	coordY = y;
	width = 28;
	height = 40;
	this->direction = direction;
	state = STAY;
	this->person = person;

	ult_timer = new Timer(30.0, 100.0, 0.0, 32.0, 32.0, ult_texture);

	idle_animation = new Animation(textures[STAY], 0, 0, 22, 40, 4, 0.03, 22);
	run_animation = new Animation(textures[RUN], 0, 0, 26, 40, 6, 0.03, 26);
	attack_animation = new Animation(textures[ATTACK], 0, 0, 28, 40, 5, 0.03, 28);

	sprite = idle_animation->Tick(false);
	sprite.setPosition(coordX, coordY);
}

Player::~Player() {
	delete idle_animation;
	delete run_animation;
	delete attack_animation;
	delete ult_timer;
	for (Bullet* b : bullets.elems) {
		delete b;
	}
}

void Player::Update() {
	if (direction == LEFT && state == RUN) {
		coordX -= PLAYER_SPEED;
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
		canShoot = false;
		sprite = attack_animation->Tick(true);
		Shoot();
	}

	if (direction == UP && state == ATTACK && canShoot) {
		canShoot = false;
		sprite = attack_animation->Tick(false);
		Shoot();
	}

	if (direction == DOWN && state == ATTACK && canShoot) {
		canShoot = false;
		sprite = attack_animation->Tick(true);
		Shoot();
	}

	if (direction == RIGHT && state == STAY) {
		sprite = idle_animation->Tick(false);
	}
	if (direction == LEFT && state == STAY) {
		sprite = idle_animation->Tick(true);
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

	sf::Time buff_time;
	buff_time = buffs_clock.getElapsedTime();
	if (buff_time.asSeconds() >= 5) {
		buffs_clock.restart();
		if (damage > 1) {
			damage--;
		}
	}

	if (damage > 1) {
		sprite.setColor(sf::Color(103, 127, 158));
	}

	controllUltimate();

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
			if (obj.type == TRAP) {
				if (canTakeDamage) {
					health--;
					sprite.setColor(sf::Color::Red);
					canTakeDamage = false;
				}
			}
		}
		if (!rect.intersects(obj.r.getGlobalBounds()) && obj.type == TRAP) {
			canTakeDamage = true;
		}
	}
}

void Player::checkBulletCollision(std::vector<Object> objects, GameObject* obj) {
	for (int i = 0; i < BULLETS_AMOUNT; i++) {
		bullets.elems[i]->checkCollision(objects);
		bullets.elems[i]->checkCollision(obj, damage);
	}
}

void Player::initBullets() {
	for (int i = 0; i < BULLETS_AMOUNT; i++) {
		bullets.push(new Bullet(-10, 10));
	}
}

void Player::checkCollisionConsumable(std::vector<Consumable*> consumable) {
	for (Consumable* c : consumable) {
		if (sprite.getGlobalBounds().intersects(c->getSprite().getGlobalBounds()) && !c->getUsed()) {
			buffs_clock.restart();
			if (c->getType() == HEALTH) {
				if (health < 5) {
					health++;
					sprite.setColor(sf::Color::Green);
				}
			}
			if (c->getType() == DAMAGE) {
				damage++;
			}
			c->Destroy();
		}
	}
}


std::deque<Bullet*> Player::getBullets() {
	return bullets.elems;
}

void Player::setState(State state) {
	this->state = state;
}

void Player::setVisible(bool v) {
	isVisible = v;
}

Person Player::getPerson() {
	return person;
}

bool Player::getVisible() {
	return isVisible;
}

Timer Player::getUltTimer() {
	return *ult_timer;
}

void Player::Shoot() {
	if (bullets.back()->getPosition().x == -10 && bullets.back()->getPosition().y == 10) {
		bullets.back()->Launch();
		bullets.back()->setPosition(coordX + width / 2, coordY + height / 2);
		bullets.back()->setDirection(direction);
		bullets.pop();
	}
}

void Player::useUltimate() {
	switch (person) {
	case VOLKOV:
		if (canUseUltimate) {
			ultimate_duration.restart();
			ultimate_cooldown.restart();
			isVisible = false;
			isUltimateWorking = true;
			canUseUltimate = false;
		}
	}
}

void Player::controllUltimate() {
	sf::Time ult_timer;
	ult_timer = ultimate_duration.getElapsedTime();
	if (ult_timer.asSeconds() >= 5) {
		ultimate_duration.restart();
		isVisible = true;
		isUltimateWorking = false;
	}

	sf::Time ult_cooldown_timer;
	ult_cooldown_timer = ultimate_cooldown.getElapsedTime();
	if (ult_cooldown_timer.asSeconds() >= 30) {
		canUseUltimate = true;
	}

	this->ult_timer->Update(ult_cooldown_timer.asSeconds());

	if (isUltimateWorking && person == VOLKOV) {
		sprite.setColor(sf::Color(255, 255, 255, 127));
	}
}
