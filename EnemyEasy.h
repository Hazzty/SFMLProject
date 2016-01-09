#ifndef ENEMYEASY
#define ENEMYEASY
#include "Enemy.h"

class EnemyEasy : public Enemy
{
public:
	virtual ~EnemyEasy(){};
	EnemyEasy(Player* player, sf::Texture* texture);
	void moveEnemy(float dt);

};

#endif