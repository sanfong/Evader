#include "Menu.h"
#define SCREEN_SIZE 800
#define SCREEN_HALF 400

Menu::Menu(RenderWindow* win, float* mul, int* scene)
{
	window = win;
	multiplier = mul;
	currentScene = scene;

	font.loadFromFile("CourierPrime.ttf");

	start.setup(Vector2f(SCREEN_HALF - 100, 400), Vector2f(200, 60), &font, "Start", Color(0, 0, 0, 50), Color(0, 0, 0, 80), Color(0, 0, 0, 120));
	scoreBoard.setup(Vector2f(SCREEN_HALF - 100, 500), Vector2f(200, 60), &font, "Scores", Color(0, 0, 0, 50), Color(0, 0, 0, 80), Color(0, 0, 0, 120));
	quit.setup(Vector2f(SCREEN_HALF - 100, 600), Vector2f(200, 60), &font, "Quit", Color(0, 0, 0, 50), Color(0, 0, 0, 80), Color(0, 0, 0, 120));
	backToMenu.setup(Vector2f(SCREEN_SIZE - 100, 0), Vector2f(100, 60), &font, "Back", Color(0, 0, 0, 50), Color(0, 0, 0, 80), Color(0, 0, 0, 120));

	start.setFontSize(30);
	scoreBoard.setFontSize(30);
	quit.setFontSize(30);

	start.isActive = true;
	scoreBoard.isActive = true;
	quit.isActive = true;
	backToMenu.isActive = true;
}

void Menu::update()
{
	mousePos = (Vector2f)Mouse::getPosition(*window);
	start.update(mousePos);
	scoreBoard.update(mousePos);
	quit.update<RenderWindow>(mousePos, window, &RenderWindow::close);
	backToMenu.update(mousePos);
}

void Menu::render()
{
	start.render(*window);
	scoreBoard.render(*window);
	quit.render(*window);
	backToMenu.render(*window);
}
