#include "../include/Enemies/Enemy.h"

Enemy::~Enemy() {
	delete idle_animation;
	delete run_animation;
	delete attack_animation;
	delete attack_borders;
	delete view_borders;
	delete health_bar;
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

HealthBar* Enemy::getHealthBar() {
	return health_bar;
}
