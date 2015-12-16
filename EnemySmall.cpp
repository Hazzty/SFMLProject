#include "EnemySmall.h"

EnemySmall::EnemySmall(float speed, float health, Player* player) : Enemy(speed, health, player)
{
	setSize(sf::Vector2f(50.f, 50.f));
	setFillColor(sf::Color::Red);
	setPosition(rand()%1280, rand()%720);
	setOrigin(getGlobalBounds().width / 2, getGlobalBounds().height / 2);
}


void EnemySmall::moveEnemy(float dt) 
{
	float dx = getPosition().x - getPlayer()->getPosition().x;
	float dy = getPosition().y - getPlayer()->getPosition().y;

	float playerRotation = ((atan2(dy, dx)) * 180 / PI) + 180;

	setRotation(playerRotation);

	setPosition(getPosition().x + (cos(getRotation()*PI / 180) * (getSpeed() * dt))
		, getPosition().y + (sin(getRotation()*PI / 180) * (getSpeed() * dt)));
}