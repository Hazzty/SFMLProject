#include "Game.h"
#define PI 3.14159265
#include <iostream>
#include <fstream>
#include <cmath>
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
	highscore = 0;

	loadHighScore();

	texture_EnemySmall.loadFromFile("Resources/enemy_fast.png");
	texture_EnemySmall.setSmooth(true);

	texture_EnemyEasy.loadFromFile("Resources/enemy_easy.png");
	texture_EnemyEasy.setSmooth(true);

	texture_PowerUp.loadFromFile("Resources/powerup.png");
}

Game::~Game()
{
	for (unsigned int i = 0; i < bullets.size(); i++)
		delete bullets.at(i);
	bullets.clear();

	for (unsigned int i = 0; i < enemies.size(); i++)
		delete enemies.at(i);
	enemies.clear();

	saveHighScore();
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

void Game::loadHighScore()
{
	std::ifstream ifs("highscore.txt");
	int scr = 0;
	if (ifs.good())
		ifs >> scr;
	ifs.close();

	highscore = scr;

}
void Game::saveHighScore()
{
	std::ofstream ofs("highscore.txt");
	ofs << highscore;
	ofs.close();
}


void Game::Update(float dt, sf::RenderWindow* window, bool isRunning)
{

	//Update framerate/frametime/enemy count/bullet count every 0.1 seconds
	if (timer_Frame >= 0.1)
	{
		window->setTitle("FPS: " + std::to_string(1/dt) + 
			" Frametime: " + std::to_string(dt) + 
			" Bullets: " + std::to_string(bullets.size()) + 
			" Enemies: " + std::to_string(enemies.size()) + 
			" EnemyMult: " + std::to_string(enemyMult) + 
			" Highscore: " + std::to_string(highscore) +
			" Score: " + std::to_string(player->getScore()));
		timer_Frame = 0;
	}
	else
		timer_Frame += dt;


	//Debug input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		for (unsigned int i = 0; i < enemies.size(); i++)
			delete enemies.at(i);
		for (unsigned int i = 0; i < bullets.size(); i++)
			delete bullets.at(i);
		for (unsigned int i = 0; i < powerups.size(); i++)
			delete powerups.at(i);
		enemies.clear();
		bullets.clear();
		powerups.clear();

		timer_Bullet = 0;
		timer_Enemy = 0;
		timer_PowerUp = 0;

		enemyMult = 1.f;
		player->setPosition(WIDTH / 2, HEIGHT / 2);
		player->setAlive(true);
		player->setDamage(1);
		player->setSpeed(300.f);
		player->setFireRate(0.2f);
		player->resetScore();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
		enemies.push_back(new EnemyEasy(player, &texture_EnemyEasy));

	//Only run the game when its not paused and if the player is alive
	if (isRunning && player->isAlive())
	{

		//=========== Player Face Cursor ==========
		sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

		float dx = player->getPosition().x - mousePos.x;
		float dy = player->getPosition().y - mousePos.y;

		float playerRotation = ((atan2(dy, dx)) * 180 / PI) + 180;

		player->setRotation(playerRotation);

		//Handle input
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
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
		



		//Move every bullet towards the direction it was originally fire towards
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
			
			for (unsigned int bI = 0; bI < bullets.size(); bI++)
			{
				if (enemies.at(eI)->getGlobalBounds().intersects(bullets.at(bI)->getGlobalBounds()) && bullets.at(bI)->isAlive())
				{
					bullets.at(bI)->setAlive(false);

					enemies.at(eI)->takeDamage(player->getDamage());
					if (enemies.at(eI)->getHealth() <= 0)
					{
						enemies.at(eI)->setAlive(false);
						player->addScore(floor(10*enemyMult));
					}

				}
			}
			sf::FloatRect playerBound = player->getGlobalBounds();
			playerBound.height -= 20; //Poor attempt at making bounding boxes more accurate

			if (enemies.at(eI)->getGlobalBounds().intersects(playerBound) && enemies.at(eI)->isAlive())
			{
				player->setAlive(false);
				if (player->getScore() > highscore)
					highscore = player->getScore();
				player->resetScore();

			}

		}

		for (unsigned int i = 0; i < powerups.size(); i++)
		{
			if (powerups.at(i)->getGlobalBounds().intersects(player->getGlobalBounds()) && powerups.at(i)->isAlive())
			{
				powerups.at(i)->applyEffect(player);
				powerups.at(i)->setAlive(false);
				
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
		
		for (unsigned int i = 0; i < powerups.size(); i++)
			if (!powerups.at(i)->isAlive())
			{
				delete powerups.at(i);
				powerups.erase(powerups.begin() + i);
			}
		
		

		/*
		Handle enemy respawns

		Spawns one fast enemy every 2 seconds, also increases the enemymult
		Which in turn acts as a score multiplier
		*/
		if (timer_Enemy >= 2.f) 
		{
			enemyMult += 0.2;
			timer_Enemy = 0;
			enemies.push_back(new EnemySmall(player, &texture_EnemySmall));
		}
		else
			timer_Enemy += dt;
		if (enemies.size() == 0)
		while (enemies.size() < enemyAmount*enemyMult) //The longer you take the more enemies will be in the next wave
			enemies.push_back(new EnemyEasy(player, &texture_EnemyEasy));

		if (timer_PowerUp >= 5.f)
		{
			switch (rand() % 3)
			{
			case 0:
				powerups.push_back(new PowerUp(FIRERATE, &texture_PowerUp));
				break;
			case 1:
				powerups.push_back(new PowerUp(DAMAGE, &texture_PowerUp));
				break;
			case 2:
				powerups.push_back(new PowerUp(SPEED, &texture_PowerUp));
				break;
			}
			
			timer_PowerUp = 0;
		}
		else
			timer_PowerUp += dt;

	}
}