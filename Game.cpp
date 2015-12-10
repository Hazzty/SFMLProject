#include "Game.h"
#define PI 3.14159265

Game::Game(sf::RenderWindow* window)
{
	this->window = window;
	player = new Player();

}

Game::~Game()
{
	bullets.clear();
	delete player;
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*player, states);

	for (unsigned int i = 0; i < bullets.size(); i++)
		target.draw(*bullets.at(i), states);

}

void Game::Update(float dt, sf::RenderWindow* window)
{
	float dx, dy, rotation;
	sf::Vector2f playerPos;
	sf::Vector2i cursorPos;

	sf::View view(sf::FloatRect(0, 0, 1280, 720));
	playerPos.x = player->getGlobalBounds().left;
	playerPos.y = player->getGlobalBounds().top;
	cursorPos = sf::Mouse::getPosition(*window);
	cursorPos = sf::Vector2i(window->mapPixelToCoords(cursorPos, view));

	dx = playerPos.x - cursorPos.x;
	dy = playerPos.y - cursorPos.y;
	rotation = (atan2(dy, dx)) * 180 / PI; //Get the angle as degrees between the two vectors, cursorPos and player pos

	player->setRotation(rotation + 180);

	window->setTitle(std::to_string(1 / dt));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		bullets.push_back(new Bullet(player, rotation + 180));
	}

	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		player->move((200.f * dt), 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		player->move(-200.f * dt, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		player->move(0, -200.f * dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		player->move(0, 200.f * dt);



	/*
	...getRot()*PI/180 converts to radians


	*/
	for (int i = 0; i < bullets.size(); i++)
		bullets.at(i)->move((cos((bullets.at(i)->getRot())*PI / 180) * bullets.at(i)->getVelocity() * dt), (sin((bullets.at(i)->getRot())*PI / 180) * bullets.at(i)->getVelocity() * dt));

	if (bullets.size() > 1000)
		bullets.erase(bullets.begin());



}