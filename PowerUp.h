#ifndef POWERUP_H
#define POWERUP_H
#include <SFML/Graphics.hpp>
#include "Player.h"

enum EFFECT{
	SPEED,
	FIRERATE,
	DAMAGE
};
class PowerUp : public sf::Sprite
{
private:
	EFFECT effect;
	Player* player;

public:
	PowerUp(EFFECT effect);
	virtual ~PowerUp();
	EFFECT getEffect() const;
	void applyEffect(Player* player);
};

#endif