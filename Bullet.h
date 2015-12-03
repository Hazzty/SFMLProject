#ifndef BULLET_H
#define BULLET_H
#include <SFML/Graphics.hpp>

class Bullet
{
private:
	float velocity;
	float rot;
	sf::CircleShape shape;
public:
	Bullet(sf::RectangleShape& player, float rot);
	sf::CircleShape* getShape();
	float getRot();
	float getVelocity();

};
#endif