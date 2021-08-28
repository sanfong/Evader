#pragma once
#include "FongFunc.h"
#include "Scene.h"
#include "Animation.h"
#include "Player.h"
#include "Obstacle.h"

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
	Vector2f deadDirection;
	Thread deadAnim;

	float score;

	vector<Player> player;
	vector<Obstacle> obs;

public:
	Game(RenderWindow* win);
	void update();
	void render();
	void spawnObs();
	void deadAnimation();
};