#include "Player.h"
#include <Windows.h>
Player::Player()
{
	health = 1;
	velocity = 200.f;
	sf::Texture text;
	text.loadFromFile("Resources/player.png");
	texture = text;
	setTexture(texture);
	setOrigin(getGlobalBounds().width / 2, getGlobalBounds().height / 2);
}
Player::Player(int health, float velocity)
{
	this->health = health;
	this->velocity = velocity;
	
	setOrigin(getGlobalBounds().width / 2, getGlobalBounds().height / 2);
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