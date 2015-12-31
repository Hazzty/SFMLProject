#ifndef ENEMYSMALL_H
#define ENEMYSMALL_H
#include "Enemy.h"
class EnemySmall : public Enemy
{
private:

public:
	EnemySmall(Player* player);
	void moveEnemy(float dt);
};

#endif