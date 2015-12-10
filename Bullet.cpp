#include "Bullet.h"


Bullet::Bullet(sf::Sprite* player, float rot)
{
	setRadius(3.f);
	setFillColor(sf::Color::White);
	setPosition(player->getPosition().x, player->getPosition().y);
	velocity = 300.f;

	this->rot = rot;
}
float Bullet::getRot() const
{
	return rot;
}
float Bullet::getVelocity() const
{
	return velocity;
}