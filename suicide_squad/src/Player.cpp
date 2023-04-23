#include <iostream>
#include <deque>

#include "../include/Player.h"

Player::Player(int x, int y, Person person, Direction direction, std::map<State, sf::Texture>& textures, sf::Texture& ult_texture) {
	bullets.setSize(BULLETS_AMOUNT);
	initBullets();

	health = 5;
	coordX = x;
	coordY = y;
	width = 32;
	height = 32;
	this->direction = direction;
	state = STAY;
	this->person = person;

	ult_timer = new Timer(30.0, 100.0, 0.0, 32.0, 32.0, ult_texture);

	idle_animation = new Animation(textures[STAY], 0, 0, 32, 32, 4, 0.03, 34);
	run_animation = new Animation(textures[RUN], 0, 0, 26, 40, 6, 0.03, 26);
	attack_animation = new Animation(textures[ATTACK], 0, 0, 28, 40, 5, 0.03, 28);

	sprite = idle_animation->Tick(false);
	sprite.setOrigin(SPRITE_SIZE / 2, SPRITE_SIZE / 2);
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

	if (s_direction == RIGHT && state == RUN) {
		coordX += PLAYER_SPEED;
	}

	if (s_direction == LEFT && state == RUN) {
		coordX -= PLAYER_SPEED;
	}

	if (direction == UP && state == RUN) {
		coordY -= PLAYER_SPEED;
	}

	if (direction == DOWN && state == RUN) {
		coordY += PLAYER_SPEED;
	}

	if (isAttacking && canShoot) {
		canShoot = false;
		Shoot();
	}

	for (int i = 0; i < BULLETS_AMOUNT; i++) {
		bullets.elems[i]->Update(angle);
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

	if (!isUltimateWorking && damage == 1) {
		sprite.setColor(sf::Color::White);
	}

	bullets.back()->setStartPoint(coordX, coordY);
	controllUltimate();

	checkDamaged();

	sprite.setRotation(angle);
	sprite.setPosition(coordX, coordY);
}

void Player::checkCollision(std::vector<Object> objects) {
	sf::FloatRect rect = this->sprite.getGlobalBounds();
	for (Object obj : objects) {
		sf::FloatRect o_rect = obj.r.getGlobalBounds();
		if (rect.intersects(obj.r.getGlobalBounds())) {
			if (obj.type == SOLID) {
				float overlapX = std::min(rect.left + rect.width, o_rect.left + o_rect.width) - std::max(rect.left, o_rect.left);
				float overlapY = std::min(rect.top + rect.height, o_rect.top + o_rect.height) - std::max(rect.top, o_rect.top);
				if (overlapX < overlapY) {
					if (rect.left < o_rect.left) {
						coordX = o_rect.left - rect.width / 2;
					}
					else {
						coordX = o_rect.left + o_rect.width + rect.width / 2;
					}
				}
				else {
					if (rect.top < o_rect.top) {
						coordY = o_rect.top - rect.height / 2;
					}
					else {
						coordY = o_rect.top + o_rect.height + rect.height / 2;
					}
				}
			}
			if (obj.type == TRAP) {
				if (canTakeDamageFromTrap) {
					health--;
					sprite.setColor(sf::Color::Red);
					canTakeDamageFromTrap = false;
				}
			}
		}
		if (!rect.intersects(obj.r.getGlobalBounds()) && obj.type == TRAP) {
			canTakeDamageFromTrap = true;
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
					c->Destroy();
				}
			}
			if (c->getType() == DAMAGE) {
				damage++;
				c->Destroy();
			}
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

void Player::setSounds(sf::SoundBuffer& attack, sf::SoundBuffer& ult) {
	attack_sound = &attack;
	ult_sound = &ult;
}

void Player::checkDamaged() {
	sf::Time damage_timer;
	damage_timer = damage_clock.getElapsedTime();
	if (!canTakeDamage) {
		sprite.setColor(sf::Color::Red);
	}

	if (damage_timer.asSeconds() >= 0.3) {
		damage_clock.restart();
		canTakeDamage = true;
		if (damage == 1 && !isUltimateWorking) {
			sprite.setColor(sf::Color::White);
		}
	}
}

void Player::takeDamage(int damage) {
	if (canTakeDamage) {
		health--;
		canTakeDamage = false;
	}
}

Person Player::getPerson() {
	return person;
}

bool Player::getVisible() {
	return isVisible;
}

void Player::setSDirection(Direction d) {
	s_direction = d;
}

Timer Player::getUltTimer() {
	return *ult_timer;
}

void Player::Shoot() {
	bullets.back()->setNxNy(nx, ny);
	bullets.back()->setAngle(angle);
	if (bullets.back()->getPosition().x == -10 && bullets.back()->getPosition().y == 10) {
		bullets.back()->Launch();
		bullets.back()->setPosition(coordX, coordY);
		bullets.back()->setDirection(direction);
		bullets.back()->setIsLaunchedByPlayer(true);
		bullets.pop();
	}
	s_manager.Shoot(attack_sound);
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
			s_manager.Ult(ult_sound);
		}
	}
}

void Player::countAngle(sf::RenderWindow& window) {
	sf::Vector2i pos = sf::Mouse::getPosition(window);
	float dX = pos.x - coordX;
	float dY = pos.y - coordY;
	this->angle = (atan2(dY, dX)) * 180 / 3.14159265;
}

void Player::countNxNy(sf::RenderWindow& window) {
	sf::Vector2i pos = sf::Mouse::getPosition(window);
	float dx = pos.x - coordX;
	float dy = pos.y - coordY;

	nx = dx / sqrt(dx * dx + dy * dy);
	ny = dy / sqrt(dx * dx + dy * dy);
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
