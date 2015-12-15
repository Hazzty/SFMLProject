#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>

class Player : public sf::Sprite
{
private:
	int health;
	float velocity;
	sf::Texture texture;

public:
	Player();
	Player(int health, float velocity);
	int getHealth() const;
	void setHealth(int const health);

	float getVelocity() const;
};


#endif