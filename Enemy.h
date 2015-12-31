#ifndef ENEMY_H
#define ENEMY_H

#include "Player.h"
#define PI 3.14159265
class Enemy : public sf::RectangleShape
{
private:
	float speed;
	float health;
	Player* player;
	bool alive;
public:
	Enemy();
	Enemy(float speed, float health, Player* player);
	~Enemy();

	Player* getPlayer();

	bool isAlive() const;
	void setAlive(bool alive);
	void takeDamage(float amount);

	void setHealth(float health);
	float getHealth() const;
	
	void setSpeed(float speed);
	float getSpeed() const;

	virtual void moveEnemy(float dt) = 0;


};

#endif