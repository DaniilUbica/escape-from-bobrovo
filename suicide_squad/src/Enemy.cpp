#include "../include/Enemy.h"

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
	view_borders = new ViewBorder(coordX, coordY, width, height, 300.0, 340.0, 150.0);

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

	attack_borders = new ViewBorder(coordX, coordY, width, height, 200.0, 230, 100.0);
	view_borders = new ViewBorder(coordX, coordY, width, height, 300.0, 340.0, 150.0);

	this->direction = direction;
	state = STAY;

	sprite.setTexture(texture);
	sprite.setOrigin(SPRITE_SIZE / 2, SPRITE_SIZE / 2);
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

		if (!view_borders->isIntersects(player) || !player->getVisible()) {
			if (!attack_borders->isIntersects(player)) {
				Patrol(ENEMY_SPEED);
			}
		}
		if (view_borders->isIntersects(player)) {
			if (player->getVisible()) {
				lookForPlayer(ENEMY_SPEED);
			}
		}

		attack_borders->Update(coordX, coordY, width, height, 100.0);
		view_borders->Update(coordX, coordY, width, height, 150.0);

		if (canAttack && attack_borders->isIntersects(player)) {
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

void Enemy::takePlayer(Player* p) {
	player = p;
}

void Enemy::setPatrolPoints(int x1, int y1, int x2, int y2) {
	this->point1_x = x1;
	this->point2_x = x2;

	this->point1_y = y1;
	this->point2_y = y2;
}

void Enemy::checkCollision(std::vector<Object> objects) {
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
		}
	}
}

void Enemy::setSounds(sf::SoundBuffer& attack) {
	attack_sound = &attack;
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

void Enemy::lookForPlayer(float speed) {

	int p_x = player->getPosition().x;
	int p_y = player->getPosition().y;

	if (!attack_borders->isIntersects(player)) {
		state = RUN;
	}

	if (!attack_borders->isIntersects(player)) {
		if (p_y == int(coordY)) {
			if (p_x > coordX) {
				direction = RIGHT;
				coordX += speed;
			}
			if (p_x < coordX) {
				direction = LEFT;
				coordX -= speed;
			}
		}
		if (p_x == int(coordX)) {
			if (p_y > coordY) {
				direction = DOWN;
				coordY += speed;
			}
			if (p_y < coordY) {
				direction = UP;
				coordY -= speed;
			}
		}
		if (p_y == int(coordY)) {
			if (p_x > coordX) {
				direction = RIGHT;
				coordX += speed;
			}
			if (p_x < coordX) {
				direction = LEFT;
				coordX -= speed;
			}
		}
		if (p_x > int(coordX)) {
			if (p_y > coordY) {
				direction = BOT_RIGHT;
				coordY += speed;
				coordX += speed;
			}
			if (p_y < coordY) {
				direction = TOP_RIGHT;
				coordY -= speed;
				coordX += speed;
			}
		}
		if (p_x < int(coordX)) {
			if (p_y > coordY) {
				direction = BOT_LEFT;
				coordY += speed;
				coordX -= speed;
			}
			if (p_y < coordY) {
				direction = TOP_LEFT;
				coordY -= speed;
				coordX -= speed;
			}
		}
	}
}

void Enemy::Patrol(float speed) {

	state = RUN;

	if (goToFirstPoint) {
		if (point1_y == int(coordY)) {
			if (point1_x < coordX) {
				direction = LEFT;
				coordX -= speed;
			}
			if (point1_x > coordX) {
				direction = RIGHT;
				coordX += speed;
			}
		}
		if (point1_x == int(coordX)) {
			if (point1_y < coordY) {
				direction = UP;
				coordY -= speed;
			}
			if (point1_y > coordY) {
				direction = DOWN;
				coordY += speed;
			}
		}
		if (point1_x > int(coordX)) {
			if (point1_y > int(coordY)) {
				direction = BOT_RIGHT;
				coordY += speed;
				coordX += speed;
			}
			if (point1_y < int(coordY)) {
				direction = TOP_RIGHT;
				coordY -= speed;
				coordX += speed;
			}
		}
		if (point1_x < int(coordX)) {
			if (point1_y > int(coordY)) {
				direction = BOT_LEFT;
				coordY += speed;
				coordX -= speed;
			}
			if (point1_y < int(coordY)) {
				direction = TOP_LEFT;
				coordY -= speed;
				coordX -= speed;
			}
		}
	}

	if (goToSecondPoint) {
		if (point2_y == int(coordY)) {
			if (point2_x < coordX) {
				direction = LEFT;
				coordX -= speed;
			}
			if (point2_x > coordX) {
				direction = RIGHT;
				coordX += speed;
			}
		}
		if (point2_x == int(coordX)) {
			if (point2_y < coordY) {
				direction = UP;
				coordY -= speed;
			}
			if (point2_y > coordY) {
				direction = DOWN;
				coordY += speed;
			}
		}
		if (point2_x > int(coordX)) {
			if (point2_y > int(coordY)) {
				direction = BOT_RIGHT;
				coordY += speed;
				coordX += speed;
			}
			if (point2_y < int(coordY)) {
				direction = TOP_RIGHT;
				coordY -= speed;
				coordX += speed;
			}
		}
		if (point2_x < int(coordX)) {
			if (point2_y > int(coordY)) {
				direction = BOT_LEFT;
				coordY += speed;
				coordX -= speed;
			}
			if (point2_y < int(coordY)) {
				direction = TOP_LEFT;
				coordY -= speed;
				coordX -= speed;
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
				Patrol(MELEE_ENEMY_SPEED);
			}
		}
		if (view_borders->isIntersects(player)) {
			if (player->getVisible()) {
				lookForPlayer(MELEE_ENEMY_SPEED);
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
		}

		sf::Time time;
		time = clock.getElapsedTime();
		if (time.asSeconds() >= 2.0) {
			clock.restart();
			canAttack = true;
		}
	}
	sprite.setPosition(coordX, coordY);

	health_bar->Update(coordX - SPRITE_SIZE/2, coordY-SPRITE_SIZE/2, health);
}
