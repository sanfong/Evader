#pragma once
#include "FongFunc.h"
#include "Scene.h"
#include "Animation.h"
#include "Player.h"
#include "Obstacle.h"
#include "Item.h"
#include "Button.h"
#include "Textbox.h"

using namespace sf;
using namespace std;

class Game : public Scene
{
private:
	Clock clock;
	int score;
	float deltaTime;
	float spawnRate;
	float currentRate;
	float fastestSpawnRate;
	float obsSpeed;
	bool gameOver;
	bool shieldOn;
	bool showEndScore;
	Vector2f mousePos;
	Texture playerTexture;
	Texture coinTexture;
	Texture donutTexture;
	Texture shieldTexture;
	Texture barrierTexture;
	Texture typingNameTexture;
	Vector2f deadDirection;
	Thread deadAnim;
	Font font;
	Text textScore;
	float lightingSpawnRate;
	float lightingClock;
	float shieldSpawnRate;
	float shieldClock;
	RectangleShape whiteAlpha;
	Text enterYourName;
	Textbox typingName;

	vector<Player> player;
	vector<Obstacle> obs;
	vector<Item> coins;
	vector<Item> donuts;
	vector<Item> shields;

	Button backToMenu;

public:
	Game(RenderWindow* win);
	void update();
	void render();
	void reset();
	void spawnShield();
	void spawnDonut();
	void spawnObs();
	void spawnCoin();
	void deadAnimation();
};