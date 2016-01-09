#include "EnemyEasy.h"


EnemyEasy::EnemyEasy(Player* player, sf::Texture* texture) : Enemy(200, 1, player, texture)
{
	setOrigin(getGlobalBounds().width / 2, getGlobalBounds().height / 2);
}


void EnemyEasy::moveEnemy(float dt)
{
	if (this->getPosition() != getPlayer()->getPosition())
	{
		float dx = getPosition().x - getPlayer()->getPosition().x;
		float dy = getPosition().y - getPlayer()->getPosition().y;

		float playerRotation = ((atan2(dy, dx)) * 180 / PI) + 180;

		setPosition(getPosition().x + (cos(playerRotation*PI / 180) * (getSpeed() * dt))
			, getPosition().y + (sin(playerRotation*PI / 180) * (getSpeed() * dt)));
	}

}