#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>

class Player : public sf::Sprite
{
private:
	int health;
	float velocity;
	sf::Texture texture;
	float firerate;

public:
	Player();
	Player(int health, float velocity);
	float getFireRate() const;
	void setFireRate(float firerate);
	int getHealth() const;
	void setHealth(int const health);

	float getVelocity() const;
};


#endif