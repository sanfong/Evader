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
	int score;
	int* currentScene;
	float deltaTime;
	float* multiplier;
	float spawnRate;
	float currentRate;
	float fastestSpawnRate;
	float obsSpeed;
	bool gameOver;
	bool shieldOn;
	Vector2f mousePos;
	Texture playerTexture;
	Texture coinTexture;
	Texture donutTexture;
	Texture shieldTexture;
	Texture barrierTexture;
	Vector2f deadDirection;
	Thread deadAnim;
	Font font;
	Text textScore;
	float lightingSpawnRate;
	Clock lightingClock;
	float shieldSpawnRate;
	Clock shieldClock;

	vector<Player> player;
	vector<Obstacle> obs;
	vector<Item> coins;
	vector<Item> donuts;
	vector<Item> shields;

public:
	Game(RenderWindow* win, float* mul, int* scene);
	void update();
	void render();
	void reset();
	void spawnShield();
	void spawnDonut();
	void spawnObs();
	void spawnCoin();
	void deadAnimation();
};