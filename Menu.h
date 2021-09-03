#pragma once
#include "FongFunc.h"
#include "Scene.h"
#include "Button.h"
#include "Game.h"

class Menu : public Scene
{
private:
	int* currentScene;
	float* multiplier;
	Vector2f mousePos;
	Font font;
	Game* game;

	Text gameName;
	Button start;
	Button scoreBoard;
	Button quit;

	Button backToMenu;
public:
	Menu(RenderWindow* win, float* mul, int* scene, Game* g);

	void update();
	void render();
};