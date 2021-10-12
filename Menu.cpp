#include "Menu.h"

Menu::Menu(RenderWindow* win, Game* g = nullptr)
{
	window = win;
	game = g;

	showScoreBG = false;
	scoreBGTexture.loadFromFile("Resources/scoreBG.jpg");
	scoreBG.setTexture(scoreBGTexture);

	font.loadFromFile("Resources/CourierPrime.ttf");

	start.setup(Vector2f(SCREEN_HALF - 100, 350), Vector2f(200, 60), &font, "Start", Color(0, 0, 0, 50), Color(0, 0, 0, 80), Color(0, 0, 0, 120));
	scoreBoard.setup(Vector2f(SCREEN_HALF - 100, 450), Vector2f(200, 60), &font, "Scores", Color(0, 0, 0, 50), Color(0, 0, 0, 80), Color(0, 0, 0, 120));
	quit.setup(Vector2f(SCREEN_HALF - 100, 550), Vector2f(200, 60), &font, "Quit", Color(0, 0, 0, 50), Color(0, 0, 0, 80), Color(0, 0, 0, 120));
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
	gameName.setPosition(Vector2f(440, 200) - (textBoxSize / 2.f));
	gameName.setFillColor(Color(randrange(0, 128), randrange(0, 128), randrange(0, 128)));
	gameName.setLetterSpacing(0.2f);

	for (size_t i = 0; i < 5; i++)
	{
		nameOnBoard[i].setFont(font);
		nameOnBoard[i].setFillColor(Color::Black);
		nameOnBoard[i].setPosition(Vector2f(120, 300 + (70 * i)));
		nameOnBoard[i].setStyle(Text::Bold);
		nameOnBoard[i].setCharacterSize(32);
		nameOnBoard[i].setLetterSpacing(0.7f);

		scoreOnBoard[i].setFont(font);
		scoreOnBoard[i].setStyle(Text::Bold);
		scoreOnBoard[i].setFillColor(Color::Black);
		scoreOnBoard[i].setPosition(Vector2f(SCREEN_SIZE - 120, 300 + (70 * i)));
		scoreOnBoard[i].setCharacterSize(32);
		scoreOnBoard[i].setLetterSpacing(0.7f);
	}
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
	if (toggle) // Score
	{
		toggle = false;
		backToMenu.isActive = true;
		showScoreBG = true;
		start.isActive = false;
		scoreBoard.isActive = false;
		quit.isActive = false;
		gameNameActive = false;

		scoreDatas = SB::getLeaderBoard();
		for (size_t i = 0; i < scoreDatas.size(); i++)
		{
			nameOnBoard[i].setString(to_string(i + 1) + "." + scoreDatas.at(i).name);

			scoreOnBoard[i].setString(to_string(scoreDatas.at(i).score));
			Vector2f scoreOnBoardSize = Vector2f(scoreOnBoard[i].getGlobalBounds().width, 0);
			scoreOnBoard[i].setOrigin(scoreOnBoardSize);
		}
	}
	else // Menu
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
	Text devName("Apinyawat Khwanpruk 64010972", font, 30);
	devName.setFillColor(Color::Black);
	Vector2f devNameSize = Vector2f(devName.getGlobalBounds().width, devName.getGlobalBounds().height);
	devName.setPosition(Vector2f(400, 770) - (devNameSize / 2.f));
	window->draw(devName);
	if (showScoreBG)
	{
		window->draw(scoreBG);
		for (size_t i = 0; i < scoreDatas.size(); i++)
		{
			window->draw(nameOnBoard[i]);
			window->draw(scoreOnBoard[i]);
		}
	}
	start.render(*window);
	scoreBoard.render(*window);
	quit.render(*window);
	backToMenu.render(*window);
	if (gameNameActive)
		window->draw(gameName);
}