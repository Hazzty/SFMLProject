#ifndef BULLET_H
#define BULLET_H
#include <SFML/Graphics.hpp>

class Bullet : public sf::CircleShape
{
private:
	float velocity;
	float rot;

public:
	Bullet(sf::Sprite* player, float rot);
	float getRot() const;
	float getVelocity() const;

};
#endif