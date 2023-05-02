#include <SFML/Graphics.hpp>
#include <map>

#include "../Player.h"
#include "../Engine/Map.h"
#include "../Bullet.h"
#include "../Enemies/Turret.h"
#include "../Enemies/EnemiesManager.h"
#include "../Enemies/ViewBorder.h"
#include "../Features/Consumable.h"
#include "../Textures.h"
#include "../Features/Portal.h"
#include "../Sound/Sounds.h"
#include "../Enemies/Boss.h"

class GameManager {
private:
	void controllPlayer(Player* player);
public:
	void Play();
};