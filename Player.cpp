#include "Player.h"
#include <Windows.h>
Player::Player()
{
	health = 1;
	speed = 300.f;
	firerate = 0.05f;
	alive = true;
	score = 0;

	sf::Texture text;
	text.loadFromFile("Resources/player.png");
	texture = text;
	texture.setSmooth(true);
	setTexture(texture);
	setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	setPosition(1280/2, 720/2);
}
Player::Player(int health, float speed)
{
	this->health = health;
	this->speed = speed;
	firerate = 0.05f;
	alive = true;

	sf::Texture text;
	text.loadFromFile("Resources/player.png");
	texture = text;
	texture.setSmooth(true);
	setTexture(texture);
	setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	setPosition(1280 / 2, 720 / 2);
}
int Player::getHealth() const
{
	return health;
}
bool Player::setHealth(int const health)
{
	if (health >= 0)
	{
		this->health = health;
		return true;
	}
	else return false;
}

float Player::getSpeed() const
{
	return speed;
}
void Player::setSpeed(float speed)
{
	this->speed = speed;

}

float Player::getFireRate() const
{
	return firerate;
}
bool Player::setFireRate(float firerate)
{
	if (firerate >= 0)
	{
		this->firerate = firerate;
		return true;
	}
	else return false;

}

bool Player::isVulnerable() const
{
	return vulnerable;
}
void Player::setVulnerable(bool vulnerable)
{
	this->vulnerable = vulnerable;
}

int Player::getDamage() const
{
	return damage;
}
void Player::setDamage(int damage)
{
	this->damage = damage;
}

bool Player::isAlive() const
{
	return alive;
}
void Player::setAlive(bool alive)
{
	this->alive = alive;
}

void Player::addScore(int score)
{
	this->score += score;
}

int Player::getScore() const
{
	return score;
}

void Player::resetScore()
{
	score = 0;
}