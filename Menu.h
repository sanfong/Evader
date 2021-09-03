#pragma once
#include "FongFunc.h"
#include "Scene.h"
#include "Button.h"

class Menu : public Scene
{
private:
	int* currentScene;
	float* multiplier;
	Vector2f mousePos;
	Font font;

	Text gameName;
	Button start;
	Button scoreBoard;
	Button quit;

	Button backToMenu;

public:
	Menu(RenderWindow* win, float* mul, int* scene);

	void update();
	void render();
};