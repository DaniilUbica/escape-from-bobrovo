#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>

#include "Enemy.h"

enum e_type {
	RANGE,
	MELEE,
};

class EnemiesManager {
private:
	std::vector<RangeEnemy*> r_enemies;
	std::vector<MeleeEnemy*> m_enemies;
	int enemies_amount;
public:
	EnemiesManager() = default;
	~EnemiesManager();

	void UpdateEnemies(Player* player);
	void checkCollision(std::vector<Object> objects);
	void addEnemy(e_type type, float x, float y, Direction direction, std::map<State, sf::Texture>& textures, int health, int p1_x, int p1_y, int p2_x, int p2_y);
	void addEnemy(e_type type, float x, float y, Direction direction, sf::Texture& texture, int health, int p1_x, int p1_y, int p2_x, int p2_y);
	void drawEnemies(sf::RenderWindow& window);
	void setBulletsTextures(sf::Texture& texture);
	void Clear();
	void Copy(EnemiesManager e);

	std::vector<RangeEnemy*> getRangeEnemies();
	std::vector<MeleeEnemy*> getMeleeEnemies();
	int getEnemiesAmount();
};

