#ifndef BULLET_H
#define BULLET_H
#include <SFML/Graphics.hpp>

class Bullet : public sf::CircleShape
{
private:
	float velocity;
	bool alive;

public:
	Bullet(sf::Sprite* player);
	
	bool isAlive() const;
	void setAlive(bool alive);
	float getVelocity() const;

};
#endif