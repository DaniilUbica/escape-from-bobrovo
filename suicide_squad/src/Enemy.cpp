#include "../include/Enemy.h"

void Enemy::Shoot() {
	state = ATTACK;
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

	shoot_borders = new ViewBorder(coordX, coordY, width, height, 2.0, 100.0, 50.0);
	view_borders = new ViewBorder(coordX, coordY, width, height, 200.0, 200.0, 150.0);

	this->direction = direction;
	state = STAY;

	idle_animation = new Animation(textures[STAY], 0, 0, 22, 48, 4, 0.02, 22);
	run_animation = new Animation(textures[RUN], 0, 0, 26, 48, 6, 0.03, 26);
	attack_animation = new Animation(textures[ATTACK], 0, 0, 28, 48, 5, 0.03, 28);

	sprite = idle_animation->Tick(false);

	sprite.setPosition(coordX, coordY);
}

Enemy::~Enemy() {
	delete idle_animation;
	delete run_animation;
	delete attack_animation;
	delete shoot_borders;
	delete view_borders;
}

void Enemy::Update() {

	if (health > 0) {

		if ((direction == RIGHT || direction == BOT_RIGHT || direction == TOP_RIGHT) && state == STAY) {
			sprite = idle_animation->Tick(false);
		}
		if ((direction == LEFT || direction == BOT_LEFT || direction == TOP_LEFT) && state == STAY) {
			sprite = idle_animation->Tick(true);
		}

		if (state == RUN && (direction == RIGHT || direction == BOT_RIGHT || direction == TOP_RIGHT)) {
			sprite = run_animation->Tick(false);
		}

		if (state == RUN && (direction == LEFT || direction == BOT_LEFT || direction == TOP_LEFT)) {
			sprite = run_animation->Tick(true);
		}

		if (!view_borders->isIntersects(player)) {
			Patrol();
		}
		if (view_borders->isIntersects(player)) {
			lookForPlayer();
		}

		shoot_borders->Update(coordX, coordY, width, height, 50.0);
		view_borders->Update(coordX, coordY, width, height, 150.0);

		if (canShoot && shoot_borders->isIntersects(player)) {
			state = ATTACK;
			direction = shoot_borders->getDirection(coordX, coordY, width, height, player);
			Shoot();
			canShoot = false;
		}

		if (state == ATTACK && (direction == LEFT || direction == BOT_LEFT || direction == TOP_LEFT)) {
			sprite = attack_animation->Tick(true);
		}
		if (state == ATTACK && (direction == RIGHT || direction == BOT_RIGHT || direction == TOP_RIGHT)) {
			sprite = attack_animation->Tick(false);
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

void Enemy::setPatrolPoints(int x1, int y1, int x2, int y2) {
	point1_x = x1;
	point2_x = x2;

	point1_y = y1;
	point2_y = y2;
}

void Enemy::checkCollision(std::vector<Object> objects) {
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

	if (!shoot_borders->isIntersects(player)) {
		state = RUN;
	}

	if (!shoot_borders->isIntersects(player)) {

		if (p_x > coordX) {
			direction = RIGHT;
			coordX += ENEMY_SPEED;
		}
		if (p_x < coordX) {
			direction = LEFT;
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

void Enemy::Patrol() {

	state = RUN;

	if (goToFirstPoint) {
		if (point1_x < coordX) {
			direction = LEFT;
			coordX -= ENEMY_SPEED;
		}
		if (point1_x > coordX) {
			direction = RIGHT;
			coordX += ENEMY_SPEED;
		}
		if (point1_y < coordY) {
			coordY -= ENEMY_SPEED;
		}
		if (point1_y > coordY) {
			coordY += ENEMY_SPEED;
		}
	}

	if (goToSecondPoint) {
		if (point2_x < coordX) {
			direction = LEFT;
			coordX -= ENEMY_SPEED;
		}
		if (point2_x > coordX) {
			direction = RIGHT;
			coordX += ENEMY_SPEED;
		}
		if (point2_y < coordY) {
			coordY -= ENEMY_SPEED;
		}
		if (point2_y > coordY) {
			coordY += ENEMY_SPEED;
		}
	}

	if (int(coordX) == point1_x && int(coordY) == point1_y) {
		goToFirstPoint = false;
		goToSecondPoint = true;
	}
	if (int(coordX) == point2_x && int(coordY) == point2_y) {
		goToFirstPoint = true;
		goToSecondPoint = false;
	}
}

std::deque<Bullet*> Enemy::getBullets() {
	return bullets.elems;
}
