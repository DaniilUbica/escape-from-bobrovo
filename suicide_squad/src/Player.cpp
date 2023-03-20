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
	sprite.setScale(2, 2);
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

	if (state == JUMP && !isFalling) {
		coordY -= JUMP_HEIGHT;
		isFalling = true;
	}

	if (direction == RIGHT && state == ATTACK) {
		isAttacking = true;
		sprite = attack_animation->Tick(false);
	}

	if (direction == LEFT && state == ATTACK) {
		isAttacking = true;
		sprite = attack_animation->Tick(true);
	}

	if (isFalling) {
		coordY += FALL_SPEED;
	}

	if (coordY >= 200) {
		isFalling = false;
	}

	if (direction == RIGHT && state == STAY) {
		sprite = idle_animation->Tick(false);
	}
	if (direction == LEFT && state == STAY) {
		sprite = idle_animation->Tick(true);
	}

	sprite.setPosition(coordX, coordY);
	sprite.setScale(3, 3);
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
