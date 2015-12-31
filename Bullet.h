#ifndef BULLET_H
#define BULLET_H
#include <SFML/Graphics.hpp>

class Bullet : public sf::CircleShape
{
private:
	float speed;
	bool alive;
	float vectorLength;
	sf::Vector2f velocity;

public:
	Bullet(sf::Sprite* player, float angleX, float angleY);
	
	bool isAlive() const;
	void setAlive(bool alive);
	float getSpeed() const;
	sf::Vector2f getVelocity() const;
};
#endif