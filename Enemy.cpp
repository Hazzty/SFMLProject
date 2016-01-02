#include "Enemy.h"


Enemy::Enemy()
{
	speed = 0.f;
	health = 0.f;
	alive = true;
}
Enemy::Enemy(float speed, float health, Player* player, sf::Texture* texture)
{
	this->speed = speed;
	this->health = health;
	this->player = player;
	this->texture = *texture;
	setTexture(this->texture);
	alive = true;

	switch (rand() % 4)
	{
	case 0:
		setPosition(UP);
		break;
	case 1:
		setPosition(RIGHT);
		break;
	case 2:
		setPosition(DOWN);
		break;
	case 3:
		setPosition(LEFT);
		break;

	}


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
	//Here be dragons
}

bool Enemy::isAlive() const
{
	return alive;
}
void Enemy::setAlive(bool alive)
{
	this->alive = alive;
}
void Enemy::takeDamage(float amount)
{
	health -= amount;
}