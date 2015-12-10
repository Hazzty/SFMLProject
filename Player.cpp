#include "Player.h"

Player::Player()
{
	health = 1;
	velocity = 200.f;
	sf::Texture texture;
	texture.loadFromFile("Resources/player.png");
	setTexture(texture);
	setTextureRect(sf::IntRect(0, 0, 150, 150));
	setOrigin(getGlobalBounds().width / 2, getGlobalBounds().height / 2);
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