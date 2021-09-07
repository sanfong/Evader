#include "Menu.h"

Menu::Menu(RenderWindow* win, Game* g = nullptr)
{
	window = win;
	game = g;

	showScoreBG = false;
	scoreBGTexture.loadFromFile("scoreBG.jpg");
	scoreBG.setTexture(scoreBGTexture);

	font.loadFromFile("CourierPrime.ttf");

	start.setup(Vector2f(SCREEN_HALF - 100, 300), Vector2f(200, 60), &font, "Start", Color(0, 0, 0, 50), Color(0, 0, 0, 80), Color(0, 0, 0, 120));
	scoreBoard.setup(Vector2f(SCREEN_HALF - 100, 400), Vector2f(200, 60), &font, "Scores", Color(0, 0, 0, 50), Color(0, 0, 0, 80), Color(0, 0, 0, 120));
	quit.setup(Vector2f(SCREEN_HALF - 100, 600), Vector2f(200, 60), &font, "Quit", Color(0, 0, 0, 50), Color(0, 0, 0, 80), Color(0, 0, 0, 120));
	backToMenu.setup(Vector2f(SCREEN_SIZE - 100, 0), Vector2f(100, 60), &font, "Back", Color(0, 0, 0, 50), Color(0, 0, 0, 80), Color(0, 0, 0, 120));

	start.setFontSize(30);
	scoreBoard.setFontSize(30);
	quit.setFontSize(30);

	gameNameActive = true;
	start.isActive = true;
	scoreBoard.isActive = true;
	quit.isActive = true;

	gameName.setFont(font);
	gameName.setStyle(Text::Bold | Text::Italic);
	gameName.setString("EVADER");
	gameName.setCharacterSize(100);
	Vector2f textBoxSize = Vector2f(gameName.getGlobalBounds().width, gameName.getGlobalBounds().height);
	gameName.setPosition(Vector2f(440, 150) - (textBoxSize / 2.f));
	gameName.setFillColor(Color(randrange(0, 128), randrange(0, 128), randrange(0, 128)));
	gameName.setLetterSpacing(0.2f);


}

void startGame(int i, Game* game)
{
	game->reset();
	changeScene(i);
}

void Menu::update()
{
	mousePos = (Vector2f)Mouse::getPosition(*window);
	start.update<int, Game*>(mousePos, startGame, 1, game);
	scoreBoard.update(mousePos, this, &Menu::toggleScoreBoard);
	quit.update<RenderWindow>(mousePos, window, &RenderWindow::close);

	backToMenu.update(mousePos, this, &Menu::toggleScoreBoard);
}

void Menu::toggleScoreBoard()
{
	static bool toggle = true;
	if (toggle)
	{
		toggle = false;
		backToMenu.isActive = true;
		showScoreBG = true;
		start.isActive = false;
		scoreBoard.isActive = false;
		quit.isActive = false;
		gameNameActive = false;
	}
	else
	{
		toggle = true;
		backToMenu.isActive = false;
		showScoreBG = false;
		start.isActive = true;
		scoreBoard.isActive = true;
		quit.isActive = true;
		gameNameActive = true;
	}
}

void Menu::render()
{
	if (showScoreBG)
		window->draw(scoreBG);
	start.render(*window);
	scoreBoard.render(*window);
	quit.render(*window);
	backToMenu.render(*window);
	if (gameNameActive)
		window->draw(gameName);
}