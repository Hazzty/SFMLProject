#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
#include "Bullet.h"
#include "Game.h"
int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
	
	Game* game = new Game(&window);
	sf::Clock dt;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		game->Update(dt.restart().asSeconds(), &window);
		window.clear();
		window.draw(*game);

		window.display();
	}

	delete game;
	return 0;
}