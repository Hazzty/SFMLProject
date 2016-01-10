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
	double timer_PowerUp;
	int enemyAmount;
	float enemyMult;
	int highscore;
	sf::Texture texture_EnemySmall;
	sf::Texture texture_EnemyEasy;
	sf::Texture texture_PowerUp;

public:
	Game(sf::RenderWindow* window);
	virtual ~Game();
	void Update(float const dt, sf::RenderWindow* window, bool isRunning);
	void loadHighScore();
	void saveHighScore();
};
#endif
