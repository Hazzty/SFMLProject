#include "Player.h"
#include <Windows.h>
Player::Player()
{
	health = 1;
	velocity = 200.f;
	sf::Texture text;
	text.loadFromFile("Resources/player2.gif");
	texture = text;
	texture.setSmooth(true);
	setTexture(texture);
	setScale(0.5, 0.5);
	setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
}
Player::Player(int health, float velocity)
{
	this->health = health;
	this->velocity = velocity;
}
int Player::getHealth() const
{
	return health;
}
void Player::setHealth(int const health)
{
	this->health = health;
}

float Player::getVelocity() const
{
	return velocity;
}