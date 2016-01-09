#include "Game.h"
#define PI 3.14159265
#include <iostream>
Game::Game(sf::RenderWindow* window)
{
	this->window = window;
	player = new Player();
	view = sf::View(sf::FloatRect(0, 0, WIDTH, HEIGHT));
	timer_Bullet = 0;
	timer_Frame = 0;
	timer_Enemy = 0;
	enemyAmount = 3; 
	enemyMult = 1.f;

	texture_EnemySmall.loadFromFile("Resources/enemy_fast.png");
	texture_EnemySmall.setSmooth(true);

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

	for (unsigned int i = 0; i < powerups.size(); i++)
		target.draw(*powerups.at(i), states);
}

void Game::Update(float dt, sf::RenderWindow* window, bool isRunning)
{

	//Update framerate/frametime/enemy count/bullet count every 0.1 seconds
	if (timer_Frame >= 0.1)
	{
		window->setTitle("You Are Blue - FPS: " + std::to_string(1/dt) + " Frametime: " + std::to_string(dt) + " Bullets: " + std::to_string(bullets.size()) + " Enemies: " + std::to_string(enemies.size()) + " EnemyMult: " + std::to_string(enemyMult));
		timer_Frame = 0;
	}
	else
		timer_Frame += dt;

	if (isRunning && player->isAlive())
	{

		//=========== Player Face Cursor ==========
		sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

		float dx = player->getPosition().x - mousePos.x;
		float dy = player->getPosition().y - mousePos.y;

		float playerRotation = ((atan2(dy, dx)) * 180 / PI) + 180;

		player->setRotation(playerRotation);

		//Handle input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Mouse::isButtonPressed(sf::Mouse::Left))
		if (timer_Bullet >= player->getFireRate())
		{
			bullets.push_back(new Bullet(player, mousePos.x - player->getPosition().x, mousePos.y - player->getPosition().y));
			timer_Bullet = 0;
		}
		else
			timer_Bullet += dt;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		if (player->getPosition().x + player->getSpeed()*dt <= WIDTH)
			player->move((player->getSpeed() * dt), 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		if (player->getPosition().x - player->getSpeed()*dt >= 0)
			player->move(-player->getSpeed() * dt, 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		if (player->getPosition().y - player->getSpeed()*dt >= 0)
			player->move(0, -player->getSpeed() * dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		if (player->getPosition().y + player->getSpeed()*dt <= HEIGHT)
			player->move(0, player->getSpeed() * dt);
		

		//Debug input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F10))
		{
			for (unsigned int i = 0; i < enemies.size(); i++)
				delete enemies.at(i);
			enemies.clear();

			enemyMult = 1.f;
			player->setPosition(WIDTH / 2, HEIGHT / 2);
			player->setAlive(true);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
			enemies.push_back(new EnemySmall(player, &texture_EnemySmall));

		//Move every bullet in the direction of the cursor
		for (Bullet* bullet : bullets)
			bullet->move(bullet->getVelocity().x * bullet->getSpeed() * dt, bullet->getVelocity().y * bullet->getSpeed() * dt);


		//If the first bulle that was fired is outside of the view, flag it for removal.
		if (!bullets.empty())
		if (bullets.front()->getPosition().x > WIDTH || bullets.front()->getPosition().x < 0 ||
			bullets.front()->getPosition().y < 0 || bullets.front()->getPosition().y > HEIGHT)
			bullets.front()->setAlive(false);

		//Move every enemy using its class unique movement pattern
		for (unsigned int i = 0; i < enemies.size(); i++)
			enemies.at(i)->moveEnemy(dt);

		//Look for collisions between bullets and enemies and the player
		for (unsigned int eI = 0; eI < enemies.size(); eI++)
		{
			sf::FloatRect currBulletBound = enemies.at(eI)->getGlobalBounds();
			currBulletBound.height -= 60;
			currBulletBound.width -= 60;


			if (player->getGlobalBounds().intersects(currBulletBound))
				player->setAlive(false);
			for (unsigned int bI = 0; bI < bullets.size(); bI++)
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
		for (unsigned int eI = 0; eI < enemies.size(); eI++)
		if (!enemies.at(eI)->isAlive())
		{
			delete enemies.at(eI);
			enemies.erase(enemies.begin() + eI);
		}

		for (unsigned int bI = 0; bI < bullets.size(); bI++)
		if (!bullets.at(bI)->isAlive())
		{
			delete bullets.at(bI);
			bullets.erase(bullets.begin() + bI);
		}
		

		//Handle enemy respawns
		if (timer_Enemy >= 1.f)
		{
			enemyMult += 0.2;
			timer_Enemy = 0;
		}
		else
			timer_Enemy += dt;
		if (enemies.size() == 0)
		while (enemies.size() < enemyAmount*enemyMult)
			enemies.push_back(new EnemySmall(player, &texture_EnemySmall));
	}
}