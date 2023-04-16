#include "../include/Enemy.h"

void RangeEnemy::Shoot() {
	state = ATTACK;
	if (bullets.back()->getPosition().x == -10 && bullets.back()->getPosition().y == 10) {
		bullets.back()->Launch();
		bullets.back()->setPosition(coordX + width / 2, coordY + height / 2);
		bullets.back()->setDirection(direction);
		bullets.pop();
	}
}

RangeEnemy::RangeEnemy(int x, int y, Direction direction, std::map<State, sf::Texture>& textures, int health) {
	bullets.setSize(BULLETS_AMOUNT);
	initBullets();

	this->health = health;

	coordX = x;
	coordY = y;

	width = 28;
	height = 40;

	health_bar = new HealthBar(coordX, coordY, health, width);

	attack_borders = new ViewBorder(coordX, coordY, width, height, 100.0, 130, 50.0);
	view_borders = new ViewBorder(coordX, coordY, width, height, 300.0, 340.0, 150.0);

	this->direction = direction;
	state = STAY;

	idle_animation = new Animation(textures[STAY], 0, 0, 22, 40, 4, 0.03, 22);
	run_animation = new Animation(textures[RUN], 0, 0, 26, 40, 6, 0.03, 26);
	attack_animation = new Animation(textures[ATTACK], 0, 0, 28, 40, 5, 0.03, 28);

	sprite = idle_animation->Tick(false);

	sprite.setPosition(coordX, coordY);
}

Enemy::~Enemy() {
	delete idle_animation;
	delete run_animation;
	delete attack_animation;
	delete attack_borders;
	delete view_borders;
	delete health_bar;
}

void RangeEnemy::Update() {

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

		if (!view_borders->isIntersects(player) || !player->getVisible()) {
			if (!attack_borders->isIntersects(player)) {
				Patrol();
			}
		}
		if (view_borders->isIntersects(player)) {
			if (player->getVisible()) {
				lookForPlayer();
			}
		}

		attack_borders->Update(coordX, coordY, width, height, 50.0);
		view_borders->Update(coordX, coordY, width, height, 150.0);

		if (canAttack && attack_borders->isIntersects(player)) {
			if (player->getVisible()) {
				state = ATTACK;
				direction = attack_borders->getDirection(coordX, coordY, width, height, player);
				Shoot();
				canAttack = false;
			}
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
			canAttack = true;
		}

		sprite.setPosition(coordX, coordY);
	}

	health_bar->Update(coordX, coordY, health);

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
				if (direction == TOP_LEFT || direction == TOP_RIGHT || direction == BOT_LEFT || direction == BOT_RIGHT) {
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

void Enemy::lookForPlayer() {

	int p_x = player->getPosition().x;
	int p_y = player->getPosition().y;

	if (!attack_borders->isIntersects(player)) {
		state = RUN;
	}

	if (!attack_borders->isIntersects(player)) {
		if (p_y == int(coordY)) {
			if (p_x > coordX) {
				direction = RIGHT;
				coordX += ENEMY_SPEED;
			}
			if (p_x < coordX) {
				direction = LEFT;
				coordX -= ENEMY_SPEED;
			}
		}
		if (p_x == int(coordX)) {
			if (p_y > coordY) {
				direction = DOWN;
				coordY += ENEMY_SPEED;
			}
			if (p_y < coordY) {
				direction = UP;
				coordY -= ENEMY_SPEED;
			}
		}
		if (p_y == int(coordY)) {
			if (p_x > coordX) {
				direction = RIGHT;
				coordX += ENEMY_SPEED;
			}
			if (p_x < coordX) {
				direction = LEFT;
				coordX -= ENEMY_SPEED;
			}
		}
		if (p_x > int(coordX)) {
			if (p_y > coordY) {
				direction = BOT_RIGHT;
				coordY += ENEMY_SPEED;
				coordX += ENEMY_SPEED;
			}
			if (p_y < coordY) {
				direction = TOP_RIGHT;
				coordY -= ENEMY_SPEED;
				coordX += ENEMY_SPEED;
			}
		}
		if (p_x < int(coordX)) {
			if (p_y > coordY) {
				direction = BOT_LEFT;
				coordY += ENEMY_SPEED;
				coordX -= ENEMY_SPEED;
			}
			if (p_y < coordY) {
				direction = TOP_LEFT;
				coordY -= ENEMY_SPEED;
				coordX -= ENEMY_SPEED;
			}
		}
	}
}

void Enemy::Patrol() {

	state = RUN;

	if (goToFirstPoint) {
		if (point1_y == int(coordY)) {
			if (point1_x < coordX) {
				direction = LEFT;
				coordX -= ENEMY_SPEED;
			}
			if (point1_x > coordX) {
				direction = RIGHT;
				coordX += ENEMY_SPEED;
			}
		}
		if (point1_x == int(coordX)) {
			if (point1_y < coordY) {
				direction = UP;
				coordY -= ENEMY_SPEED;
			}
			if (point1_y > coordY) {
				direction = DOWN;
				coordY += ENEMY_SPEED;
			}
		}
		if (point1_x > int(coordX)) {
			if (point1_y > coordY) {
				direction = BOT_RIGHT;
				coordY += ENEMY_SPEED;
				coordX += ENEMY_SPEED;
			}
			if (point1_y < coordY) {
				direction = TOP_RIGHT;
				coordY -= ENEMY_SPEED;
				coordX += ENEMY_SPEED;
			}
		}
		if (point1_x < int(coordX)) {
			if (point1_y > coordY) {
				direction = BOT_LEFT;
				coordY += ENEMY_SPEED;
				coordX -= ENEMY_SPEED;
			}
			if (point1_y < coordY) {
				direction = TOP_LEFT;
				coordY -= ENEMY_SPEED;
				coordX -= ENEMY_SPEED;
			}
		}
	}

	if (goToSecondPoint) {
		if (point2_y == int(coordY)) {
			if (point2_x < coordX) {
				direction = LEFT;
				coordX -= ENEMY_SPEED;
			}
			if (point2_x > coordX) {
				direction = RIGHT;
				coordX += ENEMY_SPEED;
			}
		}
		if (point2_x == int(coordX)) {
			if (point2_y < coordY) {
				direction = UP;
				coordY -= ENEMY_SPEED;
			}
			if (point2_y > coordY) {
				direction = DOWN;
				coordY += ENEMY_SPEED;
			}
		}
		if (point2_x > int(coordX)) {
			if (point2_y > coordY) {
				direction = BOT_RIGHT;
				coordY += ENEMY_SPEED;
				coordX += ENEMY_SPEED;
			}
			if (point2_y < coordY) {
				direction = TOP_RIGHT;
				coordY -= ENEMY_SPEED;
				coordX += ENEMY_SPEED;
			}
		}
		if (point2_x < int(coordX)) {
			if (point2_y > coordY) {
				direction = BOT_LEFT;
				coordY += ENEMY_SPEED;
				coordX -= ENEMY_SPEED;
			}
			if (point2_y < coordY) {
				direction = TOP_LEFT;
				coordY -= ENEMY_SPEED;
				coordX -= ENEMY_SPEED;
			}
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

std::deque<Bullet*> RangeEnemy::getBullets() {
	return bullets.elems;
}

HealthBar* Enemy::getHealthBar() {
	return health_bar;
}

void MeleeEnemy::Hit() {
	state = ATTACK;
	player->takeDamage(1);
}

MeleeEnemy::MeleeEnemy(int x, int y, Direction direction, sf::Texture& texture, int health) {
	this->health = health;

	coordX = x;
	coordY = y;

	width = 32;
	height = 32;

	health_bar = new HealthBar(coordX, coordY, health, width);

	attack_borders = new ViewBorder(coordX, coordY, width, height, 20.0, 52.0, 10.0);
	view_borders = new ViewBorder(coordX, coordY, width, height, 300.0, 332.0, 150.0);

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
				Patrol();
			}
		}
		if (view_borders->isIntersects(player)) {
			if (player->getVisible()) {
				lookForPlayer();
			}
		}

		attack_borders->Update(coordX, coordY, width, height, 10.0);
		view_borders->Update(coordX, coordY, width, height, 150.0);

		if (canAttack && attack_borders->isIntersects(player)) {
			if (player->getVisible()) {
				direction = attack_borders->getDirection(coordX, coordY, width, height, player);
				Hit();
				canAttack = false;
			}
		}

		if (direction == UP) {
			sprite.setRotation(0);
		}
		if (direction == DOWN) {
			sprite.setRotation(180);
		}

		if (direction == LEFT) {
			sprite.setRotation(270);
		}
		if (direction == RIGHT) {
			sprite.setRotation(90);
		}

		if (direction == TOP_LEFT) {
			sprite.setRotation(315);
		}
		if (direction == BOT_LEFT) {
			sprite.setRotation(225);
		}

		if (direction == TOP_RIGHT) {
			sprite.setRotation(45);
		}
		if (direction == BOT_RIGHT) {
			sprite.setRotation(135);
		}

		sf::Time time;
		time = clock.getElapsedTime();
		if (time.asSeconds() >= 2.0) {
			clock.restart();
			canAttack = true;
		}
		sprite.setPosition(coordX, coordY);
	}

	health_bar->Update(coordX - SPRITE_SIZE/2, coordY-SPRITE_SIZE/2, health);
}
