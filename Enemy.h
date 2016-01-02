#ifndef ENEMY_H
#define ENEMY_H

#include "Player.h"

#define WIDTH 1280
#define HEIGHT 720
#define UP rand()%WIDTH, -rand()%150
#define DOWN rand()%WIDTH, rand()%150 + HEIGHT
#define LEFT -rand()%150, rand()%HEIGHT
#define RIGHT rand()%150 + WIDTH, rand()%HEIGHT

#define PI 3.14159265
class Enemy : public sf::Sprite
{
private:
	float speed;
	float health;
	Player* player;
	bool alive;
	sf::Texture texture;
public:
	Enemy();
	Enemy(float speed, float health, Player* player, sf::Texture* texture);
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