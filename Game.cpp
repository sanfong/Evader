#include "Game.h"

using namespace sf;
using namespace std;

Game::Game(RenderWindow* win) :
	deadAnim(&Game::deadAnimation, this)
{
	window = win;
	deltaTime = 0;
	spawnRate = 2;
	currentRate = 0;
	gameOver = false;
	fastestSpawnRate = 0.5f;
	obsSpeed = 200;

	score = 0;

	coinTexture.loadFromFile("Coin.png");
	playerTexture.loadFromFile("Player.png");
	player.push_back(Player(Vector2f(100, 100), Vector2f(300, 300), 4 * 60, &playerTexture, Vector2u(4, 8), 0.2f));

	player[0].setWindowPtr(window);
}

void Game::update()
{
	deltaTime = clock.restart().asSeconds();
	mousePos = (Vector2f)Mouse::getPosition(*window);
	currentRate += deltaTime;
	if (currentRate >= spawnRate && !gameOver)
	{
		currentRate = 0;
		spawnRate = clamp(spawnRate - 0.02f, fastestSpawnRate, spawnRate);
		spawnObs();
	}

	for (size_t i = 0; i < player.size() && !gameOver; i++)
	{
		player.at(i).update(deltaTime);
		for (size_t j = 0; j < obs.size(); j++)
		{
			Obstacle& ob = obs.at(j);
			ob.update(deltaTime);
			if (ob.died)
			{
				obs.erase(obs.begin() + i);
				continue;
			}

			if (ob.getGlobalBounds().intersects(player.at(i).getGlobalBounds()))
			{
				gameOver = true;
				deadDirection = ob.getDirection();
				deadAnim.launch();
			}
		}
	}
}

void Game::render()
{
	for (size_t i = 0; i < obs.size(); i++)
	{
		obs.at(i).drawOn(*window);
	}

	for (size_t i = 0; i < player.size(); i++)
	{
		player.at(i).drawOn(*window);
	}
}

void Game::spawnObs()
{
	Vector2f spawnPos;
	Vector2f dir;
	
	float size = 80;

	switch (randrange(1, 4))
	{
	case 1: // Top
		spawnPos = Vector2f(randrange(0, 800 - size), -200);
		dir = Vector2f(0, 1);
		break;
	case 2: // Left
		spawnPos = Vector2f(-200, randrange(0, 800 - size));
		dir = Vector2f(1, 0);
		break;
	case 3: // Right
		spawnPos = Vector2f(1000, randrange(0, 800 - size));
		dir = Vector2f(-1, 0);
		break;
	case 4: // Down
		spawnPos = Vector2f(randrange(0, 800 - size), 1000);
		dir = Vector2f(0, -1);
		break;
	}

	obs.push_back(Obstacle(Vector2f(size, size), spawnPos, obsSpeed, dir, 10));
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
}
