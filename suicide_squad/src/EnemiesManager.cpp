#include "..\include\EnemiesManager.h"

EnemiesManager::~EnemiesManager() {
	for (RangeEnemy* e : r_enemies) {
		delete e;
	}

	for (MeleeEnemy* e : m_enemies) {
		delete e;
	}
}

void EnemiesManager::UpdateEnemies(Player* player) {
	for (RangeEnemy* e : r_enemies) {
		e->takePlayer(player);
		e->Update();
	}

	for (MeleeEnemy* e : m_enemies) {
		e->takePlayer(player);
		e->Update();
	}
}

void EnemiesManager::checkCollision(std::vector<Object> objects) {
	for (RangeEnemy* e : r_enemies) {
		e->checkCollision(objects);
		e->checkBulletsCollision(objects);
	}

	for (MeleeEnemy* e : m_enemies) {
		e->checkCollision(objects);
	}
}

void EnemiesManager::addEnemy(e_type type, float x, float y, Direction direction, std::map<State, sf::Texture>& textures, int health, int p1_x, int p1_y, int p2_x, int p2_y) {
	if (type == RANGE) {
		RangeEnemy* temp = new RangeEnemy(x, y, direction, textures, health);
		temp->setPatrolPoints(p1_x, p1_y, p2_x, p2_y);
		r_enemies.push_back(temp);
	}
	if (type == MELEE) {
		MeleeEnemy* temp = new MeleeEnemy(x, y, direction, textures, health);
		temp->setPatrolPoints(p1_x, p1_y, p2_x, p2_y);
		m_enemies.push_back(temp);
	}
}

void EnemiesManager::addEnemy(e_type type, float x, float y, Direction direction, sf::Texture& texture, int health, int p1_x, int p1_y, int p2_x, int p2_y) {
	if (type == RANGE) {
		RangeEnemy* temp = new RangeEnemy(x, y, direction, texture, health);
		temp->setPatrolPoints(p1_x, p1_y, p2_x, p2_y);
		r_enemies.push_back(temp);
		delete temp;
	}
	if (type == MELEE) {
		MeleeEnemy* temp = new MeleeEnemy(x, y, direction, texture, health);
		temp->setPatrolPoints(p1_x, p1_y, p2_x, p2_y);
		m_enemies.push_back(temp);
		delete temp;
	}
}

void EnemiesManager::drawEnemies(sf::RenderWindow& window) {
	for (RangeEnemy* e : r_enemies) {
		auto b = e->getBullets();
		for (int i = 0; i < BULLETS_AMOUNT; i++) {
			window.draw(b[i]->getSprite());
		}

		window.draw(e->getSprite());
		window.draw(e->getHealthBar()->getRect());
	}

	for (MeleeEnemy* e : m_enemies) {
		window.draw(e->getSprite());
		window.draw(e->getHealthBar()->getRect());
	}
}

std::vector<RangeEnemy*> EnemiesManager::getRangeEnemies()
{
	return r_enemies;
}

std::vector<MeleeEnemy*> EnemiesManager::getMeleeEnemies()
{
	return m_enemies;
}