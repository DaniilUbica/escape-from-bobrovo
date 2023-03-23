#include "../include/Player.h"

Player::Player(int x, int y, Direction direction, std::map<State, sf::Texture>& textures) {
	coordX = x;
	coordY = y;
	width = 28;
	height = 48;
	this->direction = direction;
	state = STAY;

	idle_animation = new Animation(textures[STAY], 0, 0, 22, 48, 4, 0.001, 22);
	run_animation = new Animation(textures[RUN], 0, 0, 26, 48, 6, 0.0013, 26);
	attack_animation = new Animation(textures[ATTACK], 0, 0, 28, 48, 5, 0.0013, 28);

	sprite = idle_animation->Tick(false);
	sprite.setPosition(coordX, coordY);
}

Player::~Player() {
	delete idle_animation;
	delete run_animation;
	delete attack_animation;
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

	if (state == JUMP) {
		float y = sprite.getPosition().y;
		while (coordY <= y + JUMP_HEIGHT) {
			coordY -= JUMP_SPEED;
		}
		onGround = false;
	}

	if (!onGround) {
		coordY += FALL_SPEED;
	}

	if (direction == RIGHT && state == ATTACK) {
		isAttacking = true;
		sprite = attack_animation->Tick(false);
	}

	if (direction == LEFT && state == ATTACK) {
		isAttacking = true;
		sprite = attack_animation->Tick(true);
	}

	if (direction == RIGHT && state == STAY) {
		sprite = idle_animation->Tick(false);
	}
	if (direction == LEFT && state == STAY) {
		sprite = idle_animation->Tick(true);
	}

	onGround = false;

	sprite.setPosition(coordX, coordY);
}

void Player::checkCollision(std::vector<Object> objects) {
	sf::FloatRect rect = this->sprite.getGlobalBounds();
	for (Object obj : objects) {
		if (rect.intersects(obj.r.getGlobalBounds())) {
			if (obj.type == FLOOR) {
				if (!onGround && sprite.getPosition().y < obj.r.getPosition().y) {
					coordY = obj.r.getGlobalBounds().top - height - 0.3;
					onGround = true;
				}
				if (state == JUMP) {
					coordY = obj.r.getGlobalBounds().top + obj.r.getGlobalBounds().height;
				}
			}
			if (obj.type == WALL || (obj.type == FLOOR && obj.r.getPosition().y <= sprite.getPosition().y)) {
				if (direction == LEFT && state == RUN) {
					if (obj.r.getGlobalBounds().top - TILE_SIZE >= rect.top - height) {
						coordX = obj.r.getGlobalBounds().left + obj.r.getGlobalBounds().width + 1;
					}
				}
				if (direction == RIGHT && state == RUN) {
					if (obj.r.getGlobalBounds().top - TILE_SIZE <= rect.top - height) {
						coordX = obj.r.getGlobalBounds().left - width - 1;
					}
				}
			}
		}
	}
}

sf::Sprite Player::getSprite() {
	return sprite;
}

void Player::setDirection(Direction direction) {
	this->direction = direction;
}

void Player::setState(State state) {
	this->state = state;
}
