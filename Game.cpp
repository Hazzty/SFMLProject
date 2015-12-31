#include "Game.h"
#define PI 3.14159265

Game::Game(sf::RenderWindow* window)
{
	this->window = window;
	player = new Player();
	view = sf::View(sf::FloatRect(0, 0, 1280, 720));
	timeElapsed_Bullet = 0;
	timeElapsed_Frame = 0;
	timeElapsed_Enemy = 0;
	enemyAmount = 1; 
	enemyMult = 1.f;
}

Game::~Game()
{
	for (unsigned int i = 0; i < bullets.size(); i++)
		delete bullets.at(i);
	bullets.clear();

	for (unsigned int i = 0; i < enemies.size(); i++)
		delete enemies.at(i);
	enemies.clear();

	delete player;

}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*player, states);
	
	for (unsigned int i = 0; i < enemies.size(); i++)
		target.draw(*enemies.at(i), states);

	for (unsigned int i = 0; i < bullets.size(); i++)
		target.draw(*bullets.at(i), states);
}

void Game::Update(float dt, sf::RenderWindow* window, bool isRunning)
{

	//Update framerate/frametime/enemy count/bullet count every 0.1 seconds
	if (timeElapsed_Frame >= 0.1)
	{
		window->setTitle("You Are Blue - FPS: " + std::to_string(1/dt) + " Frametime: " + std::to_string(dt) + " Bullets: " + std::to_string(bullets.size()) + " Enemies: " + std::to_string(enemies.size()) + " EnemyMult: " + std::to_string(enemyMult));
		timeElapsed_Frame = 0;
	}
	else
		timeElapsed_Frame += dt;

	if (isRunning)
	{

		//=========== Player Face Cursor ==========
		sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

		float dx = player->getPosition().x - mousePos.x;
		float dy = player->getPosition().y - mousePos.y;

		float playerRotation = ((atan2(dy, dx)) * 180 / PI) + 180;

		player->setRotation(playerRotation);

		//Handle input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Mouse::isButtonPressed(sf::Mouse::Left))
		if (timeElapsed_Bullet >= player->getFireRate())
		{
			bullets.push_back(new Bullet(player, mousePos.x - player->getPosition().x, mousePos.y - player->getPosition().y));
			timeElapsed_Bullet = 0;
		}
		else
			timeElapsed_Bullet += dt;

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

		//Move every bullet in the direction of the cursor
		for (Bullet* bullet : bullets)
			bullet->move(bullet->getVelocity().x * bullet->getSpeed() * dt, bullet->getVelocity().y * bullet->getSpeed() * dt);


		//If the first bulle that was fired is outside of the view, flag it for removal.
		if (!bullets.empty())
		if (bullets.front()->getPosition().x > 1280 || bullets.front()->getPosition().x < 0 ||
			bullets.front()->getPosition().y < 0 || bullets.front()->getPosition().y > 720)
			bullets.front()->setAlive(false);

		//Move every enemy using its class unique movement pattern
		for (int i = 0; i < enemies.size(); i++)
			enemies.at(i)->moveEnemy(dt);

		//Look for collisions between bullets and enemies
		for (int eI = 0; eI < enemies.size(); eI++)
		{
			for (int bI = 0; bI < bullets.size(); bI++)
			{
				if (enemies.at(eI)->getGlobalBounds().intersects(bullets.at(bI)->getGlobalBounds()) && bullets.at(bI)->isAlive())
				{
					bullets.at(bI)->setAlive(false);

					enemies.at(eI)->takeDamage(1.f);
					if (enemies.at(eI)->getHealth() <= 0)
						enemies.at(eI)->setAlive(false);

				}
			}
		}

		//Clean up dead enemies and bullets
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
		
		if (timeElapsed_Enemy >= 3.f)
		{
			enemyMult += 0.1;
			timeElapsed_Enemy = 0;
		}
		else
			timeElapsed_Enemy += dt;

		while (enemies.size() < enemyAmount*enemyMult)
			enemies.push_back(new EnemySmall(player));
	}
}