#pragma once
#include "FongFunc.h"
#include "Scene.h"
#include "Button.h"
#include "Game.h"
#include "Textbox.h"

class Menu : public Scene
{
private:
	Vector2f mousePos;
	Font font;
	Game* game;
	bool showScoreBG;
	Texture scoreBGTexture;
	Sprite scoreBG;

	bool gameNameActive;
	Text gameName;
	Button start;
	Button scoreBoard;
	Button quit;

	Button backToMenu;
	Textbox typingName;

public:
	Menu(RenderWindow* win, Game* g);

	void update();
	void toggleScoreBoard();
	void render();
};