#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Bullet.h"
#include <vector>

class Game : public sf::Drawable
{
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Window* window;
	std::vector<Bullet*> bullets;
	Player* player;

public:
	Game(sf::RenderWindow* window);
	~Game();
	void Update(float dt, sf::RenderWindow* window);

};
#endif
