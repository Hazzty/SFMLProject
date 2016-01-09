#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>

class Player : public sf::Sprite
{
private:
	int health;
	int damage;
	float speed;
	float firerate;
	bool vulnerable;
	sf::Texture texture;
	bool alive;
public:
	Player();
	Player(int health, float speed);
	float getFireRate() const;
	bool setFireRate(float firerate);
	int getHealth() const;
	bool setHealth(int const health);
	bool isVulnerable() const;
	void setVulnerable(bool vulnerable);
	bool isAlive() const;
	void setAlive(bool alive);

	int getDamage() const;
	void setDamage(int damage); 
	float getSpeed() const;
	void setSpeed(float speed);
};


#endif