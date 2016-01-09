#include "PowerUp.h"

PowerUp::PowerUp(EFFECT effect)
{
	this->effect = effect;

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