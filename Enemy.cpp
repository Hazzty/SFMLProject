#include "Enemy.h"

Enemy::Enemy()
{
	speed = 0.f;
	health = 0.f;
}
Enemy::Enemy(float speed, float health, Player* player)
{
	this->speed = speed;
	this->health = health;
	this->player = player;

}
Enemy::~Enemy()
{

}

Player* Enemy::getPlayer()
{
	return player;
}

void Enemy::setHealth(float health)
{
	this->health = health;
}
float Enemy::getHealth() const
{
	return health;
}

void Enemy::setSpeed(float speed)
{
	this->speed = speed;
}
float Enemy::getSpeed() const
{
	return speed;
}
void Enemy::moveEnemy(float dt)
{
	move(0, 0);
}