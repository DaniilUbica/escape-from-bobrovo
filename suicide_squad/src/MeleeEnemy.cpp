#include "../include/Enemies/MeleeEnemy.h"


void MeleeEnemy::Hit() {
	state = ATTACK;
	player->takeDamage(1);
	s_manager.Shoot(attack_sound);
}

MeleeEnemy::MeleeEnemy(int x, int y, Direction direction, std::map<State, sf::Texture>& textures, int health) {

}

MeleeEnemy::MeleeEnemy(int x, int y, Direction direction, sf::Texture& texture, int health) {
	this->health = health;

	coordX = x;
	coordY = y;

	width = 32;
	height = 32;

	health_bar = new HealthBar(coordX, coordY, health, width);

	attack_borders = new ViewBorder(coordX, coordY, width, height, 20.0, 52.0, 10.0);
	view_borders = new View(10.0, 150.0);

	this->direction = direction;
	state = STAY;

	sprite.setTexture(texture);
	sprite.setOrigin(16, 16);
	sprite.setPosition(coordX, coordY);
}

void MeleeEnemy::Update() {
	if (health > 0) {

		if (state == ATTACK) {
			sprite.setColor(sf::Color::Yellow);
		}

		if (state != ATTACK) {
			sprite.setColor(sf::Color::White);
		}

		if (!view_borders->isIntersects(player) || !player->getVisible()) {
			if (!attack_borders->isIntersects(player)) {
				Patrol(MELEE_ENEMY_SPEED);
			}
		}
		if (view_borders->isIntersects(player)) {
			if (player->getVisible()) {
				lookForPlayer(MELEE_ENEMY_SPEED);
			}
		}

		attack_borders->Update(coordX, coordY, width, height, 10.0);
		view_borders->Update(coordX, coordY, objects);

		if (canAttack && attack_borders->isIntersects(player)) {
			if (player->getVisible()) {
				direction = attack_borders->getDirection(coordX, coordY, width, height, player);
				Hit();
				canAttack = false;
			}
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

		sf::Time time;
		time = clock.getElapsedTime();
		if (time.asSeconds() >= 2.0) {
			clock.restart();
			canAttack = true;
		}
	}
	sprite.setPosition(coordX, coordY);

	health_bar->Update(coordX - SPRITE_SIZE / 2, coordY - SPRITE_SIZE / 2, health);
}
