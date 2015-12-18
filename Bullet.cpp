#include "Bullet.h"


Bullet::Bullet(sf::Sprite* player)
{
	setRadius(3.f);
	setFillColor(sf::Color::White);
	setPosition(player->getPosition().x, player->getPosition().y);
	velocity = 600.f;
	alive = true;
	setRotation(player->getRotation());
}
bool Bullet::isAlive() const
{
	return alive;
}
void Bullet::setAlive(bool alive)
{
	this->alive = alive;
}
float Bullet::getVelocity() const
{
	return velocity;
}