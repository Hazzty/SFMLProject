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

	for (int i = 0; i < bullets.size(); i++)
		bullets.at(i)->setPosition(
				bullets.at(i)->getPosition().x + (cos(bullets.at(i)->getRotation()*PI/180) * (bullets.at(i)->getVelocity() * dt))
				, bullets.at(i)->getPosition().y + (sin(bullets.at(i)->getRotation()*PI / 180) * (bullets.at(i)->getVelocity() * dt)));

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
	
	for (Enemy* enemy : enemies)
		for (Bullet* bullet: bullets)
			if (enemy->getGlobalBounds().intersects(bullet->getGlobalBounds()))
			{
				enemy->setHealth(enemy->getHealth() - 1);
			}

	
}