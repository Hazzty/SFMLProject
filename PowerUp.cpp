#include "PowerUp.h"

PowerUp::PowerUp(EFFECT effect, sf::Texture* texture)
{
	this->effect = effect;
	setPosition(rand() % 1280, rand() % 720);
	this->texture = *texture;
	setTexture(this->texture);
	alive = true;

	switch (effect)
	{
	case FIRERATE:
		this->setColor(sf::Color::Green);
		break;
	case SPEED:
		this->setColor(sf::Color::Yellow);
		break;
	case DAMAGE:
		this->setColor(sf::Color::Red);
		break;
	}


}

PowerUp::~PowerUp()
{
	//Here be dragons
}

EFFECT PowerUp::getEffect() const
{
	return effect;
}

void PowerUp::applyEffect(Player* player)
{
	switch (effect)
	{
	case SPEED:
		player->setSpeed(player->getSpeed() * 1.1f);
		break;
	case FIRERATE:
		player->setFireRate(player->getFireRate() * 0.9f);
		break;
	case DAMAGE:
		player->setDamage(player->getDamage() + 1);
		break;
	default:
		break;

	}
}

bool PowerUp::isAlive() const
{
	return alive;
}

void PowerUp::setAlive(bool alive)
{
	this->alive = alive;
}