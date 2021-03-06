#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Game.h"

int main(void)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	sf::RenderWindow window(sf::VideoMode(1280, 720), "asd");
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(false);
	window.requestFocus();
	window.clear(sf::Color::White);

	bool isRunning = true;
	sf::Clock dt;

	Game* game = new Game(&window);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::LostFocus)
				isRunning = false;
			if (event.type == sf::Event::GainedFocus)
				isRunning = true;

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
					window.close();

				if (event.key.code == sf::Keyboard::P)
				{
					if (isRunning)
						isRunning = false;
					else
						isRunning = true;
				}
			}
		}
			game->Update(dt.restart().asSeconds(), &window, isRunning);
			window.clear();
			window.draw(*game);

			window.display();

	
	}

	delete game;

	return 0;
}