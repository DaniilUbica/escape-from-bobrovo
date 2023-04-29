#include "../include/Enemies/RangeEnemy.h"

void RangeEnemy::Shoot() {
	state = ATTACK;

	float dx = player->getPosition().x - coordX;
	float dy = player->getPosition().y - coordY;

	float nx = dx / sqrt(dx * dx + dy * dy);
	float ny = dy / sqrt(dx * dx + dy * dy);

	bullets.back()->setNxNy(nx, ny);
	bullets.back()->setAngle(angle);

	if (bullets.back()->getPosition().x == -10 && bullets.back()->getPosition().y == 10) {
		bullets.back()->Launch();
		bullets.back()->setPosition(coordX, coordY);
		bullets.back()->setDirection(direction);
		bullets.pop();
	}
	s_manager.Shoot(attack_sound);
}

RangeEnemy::RangeEnemy(int x, int y, Direction direction, std::map<State, sf::Texture>& textures, int health) {
	bullets.setSize(BULLETS_AMOUNT);
	initBullets();

	this->health = health;

	coordX = x;
	coordY = y;

	width = 32;
	height = 32;

	health_bar = new HealthBar(coordX - SPRITE_SIZE / 2, coordY - SPRITE_SIZE / 2, health, width);

	attack_borders = new ViewBorder(coordX, coordY, width, height, 100.0, 130, 50.0);
	view_borders = new View(10.0, 200.0);

	this->direction = direction;
	state = STAY;

	idle_animation = new Animation(textures[STAY], 0, 0, 22, 40, 4, 0.03, 22);
	run_animation = new Animation(textures[RUN], 0, 0, 26, 40, 6, 0.03, 26);
	attack_animation = new Animation(textures[ATTACK], 0, 0, 28, 40, 5, 0.03, 28);

	sprite = idle_animation->Tick(false);
	sprite.setOrigin(SPRITE_SIZE / 2, SPRITE_SIZE / 2);
	sprite.setPosition(coordX, coordY);
}

RangeEnemy::RangeEnemy(int x, int y, Direction direction, sf::Texture& texture, int health) {
	bullets.setSize(BULLETS_AMOUNT);
	initBullets();

	this->health = health;

	coordX = x;
	coordY = y;

	width = 32;
	height = 32;

	health_bar = new HealthBar(coordX, coordY, health, width);

	attack_borders = new ViewBorder(coordX, coordY, width, height, 140, 170, 70.0);
	view_borders = new View(10.0, 250.0);

	this->direction = direction;
	state = STAY;

	sprite.setTexture(texture);
	sprite.setOrigin(SPRITE_SIZE / 2, SPRITE_SIZE / 2);
	sprite.setPosition(coordX, coordY);
}


void RangeEnemy::Update() {

	if (health > 0) {

		if (!view_borders->isIntersects(player) || !player->getVisible()) {
			Patrol(ENEMY_SPEED);
		}
		if (view_borders->isIntersects(player)) {
			if (player->getVisible()) {
				lookForPlayer(ENEMY_SPEED);
			}
		}

		attack_borders->Update(coordX, coordY, width, height, 100.0);
		view_borders->Update(coordX, coordY, objects);

		if (canAttack && attack_borders->isIntersects(player) && view_borders->isIntersects(player)) {
			if (player->getVisible()) {
				state = ATTACK;
				direction = attack_borders->getDirection(coordX, coordY, width, height, player);
				Shoot();
				canAttack = false;
			}
		}

		sf::Time time;
		time = clock.getElapsedTime();
		if (time.asSeconds() >= 1.0) {
			clock.restart();
			canAttack = true;
		}

		if (state != RUN) {
			sf::Vector2f pos = player->getPosition();
			float dX = pos.x - coordX;
			float dY = pos.y - coordY;
			float rotation = (atan2(dY, dX)) * 180 / 3.14159265;
			sprite.setRotation(rotation);
			angle = rotation;
		}

		if (state == RUN) {
			if (direction == UP) {
				sprite.setRotation(270);
			}
			if (direction == DOWN) {
				sprite.setRotation(90);
			}

			if (direction == LEFT) {
				sprite.setRotation(180);
			}
			if (direction == RIGHT) {
				sprite.setRotation(0);
			}

			if (direction == TOP_LEFT) {
				sprite.setRotation(225);
			}
			if (direction == BOT_LEFT) {
				sprite.setRotation(135);
			}
			if (direction == TOP_RIGHT) {
				sprite.setRotation(315);
			}
			if (direction == BOT_RIGHT) {
				sprite.setRotation(45);
			}
		}
	}

	sprite.setPosition(coordX, coordY);
	sprite.setColor(sf::Color::White);

	health_bar->Update(coordX - SPRITE_SIZE / 2, coordY - SPRITE_SIZE / 2, health);

	for (int i = 0; i < BULLETS_AMOUNT; i++) {
		bullets.elems[i]->Update(angle);
	}
}


void RangeEnemy::initBullets() {
	for (int i = 0; i < BULLETS_AMOUNT; i++) {
		bullets.push(new Bullet(-10, 10));
	}
}

void RangeEnemy::checkBulletsCollision(std::vector<Object> objects) {

	for (int i = 0; i < BULLETS_AMOUNT; i++) {
		bullets.elems[i]->checkCollision(player);
		bullets.elems[i]->checkCollision(objects);
	}
}


std::deque<Bullet*> RangeEnemy::getBullets() {
	return bullets.elems;
}
