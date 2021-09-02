#include "Game.h"

using namespace sf;
using namespace std;

const int SCREEN_SIZE = 800;

Game::Game(RenderWindow* win, float* mul, int* scene) :
	deadAnim(&Game::deadAnimation, this)
{
	window = win;
	score = 0;
	deltaTime = 0;
	multiplier = mul;
	currentScene = scene;
	spawnRate = 2;
	currentRate = 0;
	gameOver = false;
	shieldOn = false;
	fastestSpawnRate = 0.5f;
	obsSpeed = 200;
	lightingSpawnRate = 60;
	shieldSpawnRate = 120;

	font.loadFromFile("CourierPrime.ttf");
	textScore.setFont(font);
	textScore.setFillColor(Color::Black);
	textScore.setCharacterSize(30);
	textScore.setString("Score: " + to_string(score));

	shieldTexture.loadFromFile("Shield.png");
	donutTexture.loadFromFile("Donut.png");
	coinTexture.loadFromFile("Coin.png");

	playerTexture.loadFromFile("Player.png");
	player.push_back(Player(Vector2f(100, 100), Vector2f(400, 400), 4 * 60, &playerTexture, Vector2u(4, 8), 0.2f));
	player[0].setWindowPtr(window);

	barrierTexture.loadFromFile("Barrier-Sheet.png");
	player[0].effectShape.setTexture(&barrierTexture);
	player[0].effectShape.setTextureRect(IntRect(0, 0, 64, 64));
}

void Game::update()
{
	deltaTime = clock.restart().asSeconds() * *multiplier;
	mousePos = (Vector2f)Mouse::getPosition(*window);
	currentRate += deltaTime;
	// Item spawn
	if (!gameOver)
	{
		if (currentRate >= spawnRate)
		{
			currentRate = 0;
			spawnRate = clamp(spawnRate - 0.01f, fastestSpawnRate, spawnRate);
			cout << spawnRate << endl;
			spawnObs();
			spawnCoin();
		}
		if (lightingClock.getElapsedTime().asSeconds() > lightingSpawnRate)
		{
			lightingClock.restart();
			lightingSpawnRate = randrange(45, 60);
			spawnDonut();
		}
		if (shieldClock.getElapsedTime().asSeconds() > shieldSpawnRate)
		{
			shieldClock.restart();
			shieldSpawnRate = randrange(45, 60);
			spawnShield();
		}
	}

	for (size_t p = 0; p < player.size() && !gameOver; p++)
	{
		player.at(p).update(deltaTime);
		// Obstacle
		for (size_t i = 0; i < obs.size(); i++)
		{
			Obstacle& ob = obs.at(i);
			ob.update(deltaTime);
			if (ob.died)
			{
				obs.erase(obs.begin() + i);
				continue;
			}
			if (ob.getGlobalBounds().intersects(player.at(p).getGlobalBounds()))
			{
				if (shieldOn)
				{
					shieldOn = false;
					obs.erase(obs.begin() + i);
				}
				else
				{
					gameOver = true;
					deadDirection = ob.getDirection();
					deadAnim.launch();
				}
			}
		}

		// Coins
		for (size_t i = 0; i < coins.size(); i++)
		{
			Item& coin = coins.at(i);
			coin.update(deltaTime);
			if (coin.died)
			{
				coins.erase(coins.begin() + i);
				continue;
			}
			if (coin.getGlobalBounds().intersects(player.at(p).getGlobalBounds()))
			{
				coins.erase(coins.begin() + i);
				score += 10;
				textScore.setString("Score: " + to_string(score));
			}
		}

		// Donuts
		for (size_t i = 0; i < donuts.size(); i++)
		{
			Item& donut = donuts.at(i);
			donut.update(deltaTime);
			if (donut.died)
			{
				donuts.erase(donuts.begin() + i);
				lightingSpawnRate = randrange(50, 60);
				continue;
			}
			if (donut.getGlobalBounds().intersects(player.at(p).getGlobalBounds()))
			{
				donuts.erase(donuts.begin() + i);
				player.at(p).setBoost(10);
			}
		}

		// Shield
		for (size_t i = 0; i < shields.size(); i++)
		{
			Item& shield = shields.at(i);
			shield.update(deltaTime);
			if (shield.died)
			{
				shields.erase(shields.begin() + i);
				shieldSpawnRate = randrange(50, 60);
				continue;
			}
			if (shield.getGlobalBounds().intersects(player.at(p).getGlobalBounds()))
			{
				shields.erase(shields.begin() + i);
				shieldOn = true;
			}
		}
	}
}

void Game::render()
{
	for (size_t i = 0; i < donuts.size(); i++)
	{
		donuts.at(i).drawOn(*window);
	}

	for (size_t i = 0; i < shields.size(); i++)
	{
		shields.at(i).drawOn(*window);
	}

	for (size_t i = 0; i < coins.size(); i++)
	{
		coins.at(i).drawOn(*window);
	}

	for (size_t i = 0; i < obs.size(); i++)
	{
		obs.at(i).drawOn(*window);
	}

	for (size_t i = 0; i < player.size(); i++)
	{
		player.at(i).drawOn(*window);
		if (shieldOn)
		{
			window->draw(player.at(i).effectShape);
		}
	}

	window->draw(textScore);
}

void Game::reset()
{
	score = 0;
	spawnRate = 2;
	currentRate = 0;
	gameOver = false;
	shieldOn = false;
	fastestSpawnRate = 0.6f;
	lightingSpawnRate = 60;
	shieldSpawnRate = 90;

	textScore.setPosition(Vector2f(0, 0));
	textScore.setString("Score: " + to_string(score));
	textScore.setCharacterSize(30);

	player.push_back(Player(Vector2f(100, 100), Vector2f(400, 400), 4 * 60, &playerTexture, Vector2u(4, 8), 0.2f));

	player[0].effectShape.setTexture(&barrierTexture);
	player[0].effectShape.setTextureRect(IntRect(0, 0, 64, 64));
}

void Game::spawnShield()
{
	float size = 50;
	Vector2f spawnPos = Vector2f(randrange(0, SCREEN_SIZE - size), randrange(0, SCREEN_SIZE - size));
	shields.push_back(Item(Vector2f(size, size), spawnPos, &shieldTexture, 15));
}

void Game::spawnDonut()
{
	float size = 50;
	Vector2f spawnPos = Vector2f(randrange(0, SCREEN_SIZE - size), randrange(0, SCREEN_SIZE - size));
	donuts.push_back(Item(Vector2f(size, size), spawnPos, &donutTexture, 15));
}

void Game::spawnObs()
{
	Vector2f spawnPos;
	Vector2f dir;
	
	float size = 80;

	switch (randrange(1, 4))
	{
	case 1: // Top
		spawnPos = Vector2f(randrange(0, SCREEN_SIZE - size), -200);
		dir = Vector2f(0, 1);
		break;
	case 2: // Left
		spawnPos = Vector2f(-200, randrange(0, SCREEN_SIZE - size));
		dir = Vector2f(1, 0);
		break;
	case 3: // Right
		spawnPos = Vector2f(1000, randrange(0, SCREEN_SIZE - size));
		dir = Vector2f(-1, 0);
		break;
	case 4: // Down
		spawnPos = Vector2f(randrange(0, SCREEN_SIZE - size), 1000);
		dir = Vector2f(0, -1);
		break;
	}

	obs.push_back(Obstacle(Vector2f(size, size), spawnPos, obsSpeed, dir, 10));
}

void Game::spawnCoin()
{
	float size = 50;
	Vector2f spawnPos = Vector2f(randrange(0, SCREEN_SIZE - size), randrange(0, SCREEN_SIZE - size));
	coins.push_back(Item(Vector2f(size, size), spawnPos, &coinTexture, 30));
}

void Game::deadAnimation()
{
	float flyingSpeed = 1000;
	float rotateSpeed = 360 * 3;
	float deltaTime = 0.0;
	Clock clock;
	for (float duration = 1; duration > 0; duration -= deltaTime)
	{
		deltaTime = clock.restart().asSeconds();
		for (size_t i = 0; i < player.size(); i++)
		{
			player.at(i).move(deadDirection * flyingSpeed * deltaTime);
			player.at(i).rotate(rotateSpeed * deltaTime);
		}
	}
	player.clear();
	Vector2f textBoxSize = Vector2f(textScore.getGlobalBounds().width, textScore.getGlobalBounds().height);
}
