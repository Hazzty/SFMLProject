#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Bullet.h"
#include <vector>
#include "EnemySmall.h"
#include "EnemyEasy.h"
#include "PowerUp.h"

class Game : public sf::Drawable
{
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Window* window;
	std::vector<Bullet*> bullets;
	std::vector<Enemy*> enemies;
	std::vector<PowerUp*> powerups;
	Player* player;
	sf::View view;
	double timer_Bullet;
	double timer_Frame;
	double timer_Enemy;
	double timer_powerUp;
	int enemyAmount;
	float enemyMult;
	sf::Texture texture_EnemySmall;
	sf::Texture texture_EnemyEasy;

public:
	Game(sf::RenderWindow* window);
	~Game();
	void Update(float dt, sf::RenderWindow* window, bool isRunning);

};
#endif
