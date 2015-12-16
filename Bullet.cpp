#include "Bullet.h"


Bullet::Bullet(sf::Sprite* player)
{
	setRadius(3.f);
	setFillColor(sf::Color::White);
	setPosition(player->getPosition().x, player->getPosition().y);
	velocity = 600.f;
	rot = player->getRotation();
	setRotation(rot);
}
float Bullet::getRot() const
{
	return rot;
}
float Bullet::getVelocity() const
{
	return velocity;
}