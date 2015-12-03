#include "Bullet.h"


Bullet::Bullet(sf::RectangleShape& player, float rot)
{
	shape = sf::CircleShape(3.f);
	shape.setFillColor(sf::Color::White);
	shape.setPosition(player.getPosition().x, player.getPosition().y);
	velocity = 400.f;

	this->rot = rot;
}

float Bullet::getRot()
{
	return rot;
}
float Bullet::getVelocity()
{
	return velocity;
}
sf::CircleShape* Bullet::getShape()
{
	return &shape;
}