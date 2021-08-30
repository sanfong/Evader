#pragma once
#include "FongFunc.h"
#include "Scene.h"
#include "Animation.h"
#include "Player.h"
#include "Obstacle.h"
#include "Item.h"

using namespace sf;
using namespace std;

class Game : public Scene
{
private:
	Clock clock;
	float deltaTime;
	float spawnRate;
	float currentRate;
	float fastestSpawnRate;
	float obsSpeed;
	bool gameOver;
	Vector2f mousePos;
	Texture playerTexture;
	Texture coinTexture;
	Texture donutTexture;
	Vector2f deadDirection;
	Thread deadAnim;
	Font font;
	Text textScore;
	float lightingSpawnRate;
	Clock lightingClock;

	int score;

	vector<Player> player;
	vector<Obstacle> obs;
	vector<Item> coins;
	vector<Item> donuts;

public:
	Game(RenderWindow* win);
	void update();
	void render();
	void spawnDonut();
	void spawnObs();
	void spawnCoin();
	void deadAnimation();
};