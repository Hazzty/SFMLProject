#include "Game.h"
#define PI 3.14159265
double bulletTime = 0;
double frameRateTimer = 0;
Game::Game(sf::RenderWindow* window)
{
	this->window = window;
	player = new Player();
	view = sf::View(sf::FloatRect(0, 0, 1280, 720));
	for (int i = 0; i < 10; i++)
		enemies.push_back(new EnemySmall(200, 3, player));
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
	for (unsigned int i = 0; i < enemies.size(); i++)
		target.draw(*enemies.at(i), states);

}

void Game::Update(float dt, sf::RenderWindow* window)
{
	if (frameRateTimer >= 0.1)
	{
		window->setTitle("You Are Blue - FPS: " + std::to_string(1/dt) + " Frametime: " + std::to_string(dt) + " Bullets: " + std::to_string(bullets.size()));
		frameRateTimer = 0;
	}
	else
		frameRateTimer += dt;
	//=========== Player Face Cursor ==========
	sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

	float dx = player->getPosition().x - mousePos.x;
	float dy = player->getPosition().y - mousePos.y;

	float playerRotation = ((atan2(dy, dx)) * 180 / PI) + 180;

	player->setRotation(playerRotation);

	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Mouse::isButtonPressed(sf::Mouse::Left))
		if (bulletTime >= 0.1)
		{
			bullets.push_back(new Bullet(player));
			bulletTime = 0;
		}
		else
			bulletTime += dt;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		if (player->getPosition().x + player->getVelocity()*dt <= 1280)
			player->move((player->getVelocity() * dt), 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		if (player->getPosition().x - player->getVelocity()*dt >= 0)
		player->move(-player->getVelocity() * dt, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		if (player->getPosition().y - player->getVelocity()*dt >= 0)
		player->move(0, -player->getVelocity() * dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		if (player->getPosition().y + player->getVelocity()*dt <= 720)
		player->move(0, player->getVelocity() * dt);

	for (Bullet* bullet: bullets)
		bullet->setPosition(
				bullet->getPosition().x + (cos(bullet->getRotation()*PI/180) * (bullet->getVelocity() * dt))
				, bullet->getPosition().y + (sin(bullet->getRotation()*PI / 180) * (bullet->getVelocity() * dt)));

	if (!bullets.empty())
	{
		if (bullets.front()->getPosition().x > 1280 || bullets.front()->getPosition().x < 0 || bullets.front()->getPosition().y < 0 || bullets.front()->getPosition().y > 720 || bullets.size() >= 100)
		{
			delete *bullets.begin();
			bullets.erase(bullets.begin());
		}
	}
		

	for (int i = 0; i < enemies.size(); i++)
		enemies.at(i)->moveEnemy(dt);

	for (int eI = 0; eI < enemies.size(); eI++)
	{
		for (int bI = 0; bI < bullets.size(); bI++)
		{
			if (enemies.at(eI)->getGlobalBounds().intersects(bullets.at(bI)->getGlobalBounds()))
			{
				enemies.at(eI)->takeDamage(1.f);
				if (enemies.at(eI)->getHealth() <= 0)
					enemies.at(eI)->setAlive(false);
	
				bullets.at(bI)->setAlive(false);

			}
		}
	}

	for (int eI = 0; eI < enemies.size(); eI++)
		if (!enemies.at(eI)->isAlive())
		{
			delete enemies.at(eI);
			enemies.erase(enemies.begin() + eI);
		}
		
	for (int bI = 0; bI < bullets.size(); bI++)
		if (!bullets.at(bI)->isAlive())
		{
			delete bullets.at(bI);
			bullets.erase(bullets.begin() + bI);
		}
	
}