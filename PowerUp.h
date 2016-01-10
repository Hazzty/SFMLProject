#ifndef POWERUP_H
#define POWERUP_H
#include <SFML/Graphics.hpp>
#include "Player.h"

enum EFFECT{
	SPEED = 0,
	FIRERATE = 1,
	DAMAGE = 2
};
class PowerUp : public sf::Sprite
{
private:
	EFFECT effect;
	Player* player;
	sf::Texture texture;
	bool alive;

public:
	PowerUp(EFFECT effect, sf::Texture* texture);
	virtual ~PowerUp();
	EFFECT getEffect() const;
	void applyEffect(Player* player);
	bool isAlive() const;
	void setAlive(bool alive);
};

#endif