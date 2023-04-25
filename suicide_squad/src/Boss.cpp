#include "../include/Enemies/Boss.h"

void Boss::Shoot() {
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

void Boss::Hit() {
	state = ATTACK;
	player->takeDamage(1);
	s_manager.Shoot(attack_sound);
}

void Boss::initBullets() {
	for (int i = 0; i < BULLETS_AMOUNT; i++) {
		bullets.push(new Bullet(-10, 10));
	}
}

Boss::Boss(int x, int y, Direction direction, std::map<State, sf::Texture>& textures, int health) {

}

Boss::Boss(int x, int y, Direction direction, sf::Texture& texture, int health) {
	bullets.setSize(BULLETS_AMOUNT);
	initBullets();

	this->health = health;

	coordX = x;
	coordY = y;

	width = 64;
	height = 64;

	health_bar = new HealthBar(coordX, coordY, health, width);

	attack_borders = new ViewBorder(coordX, coordY, width, height, 900.0, 330, 450.0);
	view_borders = new ViewBorder(coordX, coordY, width, height, 1300.0, 740.0, 650.0);
	hit_borders = new ViewBorder(coordX, coordY, width, height, 20.0, 52.0, 10.0);

	this->direction = direction;
	state = STAY;

	sprite.setTexture(texture);
	sprite.setOrigin(SPRITE_SIZE, SPRITE_SIZE);
	sprite.setPosition(coordX, coordY);
}

Boss::~Boss() {
	delete idle_animation;
	delete run_animation;
	delete attack_animation;
	delete attack_borders;
	delete view_borders;
	delete hit_borders;
	delete health_bar;
}

void Boss::checkBulletsCollision(std::vector<Object> objects) {
	for (int i = 0; i < BULLETS_AMOUNT; i++) {
		bullets.elems[i]->checkCollision(player);
		bullets.elems[i]->checkCollision(objects);
		for (int i = 0; i < BULLETS_AMOUNT; i++) {
			player->checkBulletCollision(bullets.elems[i]);
		}
	}
}

void Boss::Update() {
	if (health > 0) {

		if (!view_borders->isIntersects(player) || !player->getVisible()) {
			if (!attack_borders->isIntersects(player)) {
				Patrol(ENEMY_SPEED);
			}
		}
		if (view_borders->isIntersects(player)) {
			if (player->getVisible()) {
				lookForPlayer(ENEMY_SPEED/2);
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
		if (time.asSeconds() >= 0.5) {
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
		bullets.elems[i]->Update(player);
	}
}

void Boss::checkCollision(std::vector<Object> objects) {
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

void Boss::lookForPlayer(float speed) {
	int p_x = player->getPosition().x;
	int p_y = player->getPosition().y;

	if (!attack_borders->isIntersects(player)) {
		state = RUN;
	}

	if (!hit_borders->isIntersects(player)) {
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

void Boss::setBulletsTextures(sf::Texture* textures) {
	srand(time(NULL));

	for (int i = 0; i < BULLETS_AMOUNT; i++) {
		bullets.elems[i]->setTexture(textures[rand()%BULLETS_AMOUNT+0]);
	}
}

std::deque<Bullet*> Boss::getBullets() {
	return bullets.elems;
}
