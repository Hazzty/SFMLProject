#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
#include "Bullet.h"
int main()
{
	std::vector<Bullet*> bullets;
	const float PI = 3.14159265;
	sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
	sf::View view(sf::FloatRect(0, 0, 1000, 600));
	window.setView(view);
	window.setFramerateLimit(60);
	sf::RectangleShape player;
	player.setSize(sf::Vector2f(20, 20));
	player.setFillColor(sf::Color::Blue);
	player.setOrigin(player.getLocalBounds().width / 2, player.getLocalBounds().height/2);
	sf::Clock clock;

	float dx, dy, rotation;
	sf::Vector2f playerPos;
	sf::Vector2i cursorPos;
	sf::Time elapsed;
	while (window.isOpen())
	{


		playerPos.x = player.getGlobalBounds().left;
		playerPos.y = player.getGlobalBounds().top;
		cursorPos = sf::Mouse::getPosition(window);
		cursorPos = sf::Vector2i(window.mapPixelToCoords(cursorPos, view));

		

		dx = playerPos.x - cursorPos.x;
		dy = playerPos.y - cursorPos.y;
		rotation = (atan2(dy, dx)) * 180 / PI; //Get the angle as degrees between the two vectors, cursorPos and player pos

		player.setRotation(rotation + 180);
		sf::Time dt= clock.restart();
		window.setTitle(std::to_string(dt.asSeconds()));

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			elapsed = clock.getElapsedTime();
			if (elapsed.asSeconds() > 0.0001f )
			{
				bullets.push_back(new Bullet(player, rotation + 180));
				elapsed = sf::milliseconds(0);
			}

		}
			
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			player.move((200.f*dt.asSeconds()), 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			player.move(-200.f * dt.asSeconds(), 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			player.move(0, -200.f * dt.asSeconds());
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			player.move(0, 200.f * dt.asSeconds());


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		/*
			...getRot()*PI
			
			
		*/
		for (int i = 0; i < bullets.size(); i++)
			bullets.at(i)->getShape()->move((cos((bullets.at(i)->getRot())*PI / 180) * 300.f * dt.asSeconds()), (sin((bullets.at(i)->getRot())*PI / 180) * 300.f * dt.asSeconds()));

		if (bullets.size() > 1000)
			bullets.erase(bullets.begin());

		window.clear();

		for (int i = 0; i < bullets.size(); i++)
			window.draw(*bullets.at(i)->getShape());

		window.draw(player);
		window.display();
	}

	return 0;
}