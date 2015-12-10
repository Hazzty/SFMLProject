#ifndef BULLET_H
#define BULLET_H
#include <SFML/Graphics.hpp>

class Bullet : sf::CircleShape
{
private:
	float velocity;
	float rot;

public:
	Bullet(sf::Sprite* player, float rot);
	float getRot();
	float getVelocity();

};
#endif