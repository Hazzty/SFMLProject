#include "Bullet.h"


Bullet::Bullet(sf::Sprite* player, float angleX, float angleY)
{

	this->vectorLength = sqrt(angleX*angleX + angleY*angleY);
	velocity.x = (angleX / vectorLength);
	velocity.y = (angleY / vectorLength);
	setRadius(3.f);
	setFillColor(sf::Color::White);
	setPosition(player->getPosition().x, player->getPosition().y);
	speed = 600.f;
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
float Bullet::getSpeed() const
{
	return speed;
}

sf::Vector2f Bullet::getVelocity() const
{
	return velocity;
}