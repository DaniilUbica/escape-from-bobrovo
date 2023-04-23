#include "..\include\EnemiesManager.h"

#include <algorithm>

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
		if (e->getHP() <= 0 && e->getPosition().x != -1000) {
			killed_enemies++;
			//r_enemies.erase(find(r_enemies.begin(),r_enemies.end(),e));
			e->setPosition(-1000, -1000);
		}
	}

	for (MeleeEnemy* e : m_enemies) {
		e->takePlayer(player);
		e->Update();
		if (e->getHP() <= 0 && e->getPosition().x != -1000) {
			killed_enemies++;
			//m_enemies.erase(find(m_enemies.begin(), m_enemies.end(), e));
			e->setPosition(-1000, -1000);
		}
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
		r_enemies.push_back(new RangeEnemy(x, y, direction, textures, health));
		r_enemies[r_enemies.size() - 1]->setPatrolPoints(p1_x, p1_y, p2_x, p2_y);
	}
	if (type == MELEE) {
		m_enemies.push_back(new MeleeEnemy(x, y, direction, textures, health));
		m_enemies[m_enemies.size() - 1]->setPatrolPoints(p1_x, p1_y, p2_x, p2_y);
	}
	enemies_amount = r_enemies.size() + m_enemies.size();
}

void EnemiesManager::addEnemy(e_type type, float x, float y, Direction direction, sf::Texture& texture, int health, int p1_x, int p1_y, int p2_x, int p2_y) {
	if (type == RANGE) {
		r_enemies.push_back(new RangeEnemy(x, y, direction, texture, health));
		r_enemies[r_enemies.size() - 1]->setPatrolPoints(p1_x, p1_y, p2_x, p2_y);
	}
	if (type == MELEE) {
		m_enemies.push_back(new MeleeEnemy(x, y, direction, texture, health));
		m_enemies[m_enemies.size() - 1]->setPatrolPoints(p1_x, p1_y, p2_x, p2_y);
	}
	enemies_amount = r_enemies.size() + m_enemies.size();
}

void EnemiesManager::drawEnemies(sf::RenderWindow& window) {
	for (RangeEnemy* e : r_enemies) {
		auto b = e->getBullets();
		for (int i = 0; i < BULLETS_AMOUNT; i++) {
			window.draw(b[i]->getSprite());
		}

		window.draw(e->getSprite());
		e->getHealthBar()->drawHealthBar(window);
	}

	for (MeleeEnemy* e : m_enemies) {
		window.draw(e->getSprite());
		e->getHealthBar()->drawHealthBar(window);
	}
}

void EnemiesManager::setBulletsTextures(sf::Texture& texture) {
	for (RangeEnemy* e : r_enemies) {
		for (int i = 0; i < BULLETS_AMOUNT; i++) {
			e->getBullets()[i]->setTexture(texture);
		}
	}
}

void EnemiesManager::Clear() {
	r_enemies.clear();
	m_enemies.clear();
}

void EnemiesManager::Copy(EnemiesManager e) {
	r_enemies = e.getRangeEnemies();
	m_enemies = e.getMeleeEnemies();
}

void EnemiesManager::setSounds(sf::SoundBuffer& attack, sf::SoundBuffer& hit) {
	for (RangeEnemy* e : r_enemies) {
		e->setSounds(attack);
	}
	for (MeleeEnemy* e : m_enemies) {
		e->setSounds(hit);
	}
}

void EnemiesManager::setKilledToNull() {
	killed_enemies = 0;
}

std::vector<RangeEnemy*> EnemiesManager::getRangeEnemies()
{
	return r_enemies;
}

std::vector<MeleeEnemy*> EnemiesManager::getMeleeEnemies()
{
	return m_enemies;
}

int EnemiesManager::getEnemiesAmount() {
	return enemies_amount;
}

int EnemiesManager::getKilledEnemies() {
	return killed_enemies;
}
