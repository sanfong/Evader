#include "FongFunc.h"
#include "Scene.h"
#include "Game.h"

using namespace sf;
using namespace std;

float multiplier = 1;

int main()
{
	RenderWindow window(VideoMode(800, 800), "Game", Style::Close);
	window.setFramerateLimit(60);

	srand(time(0));
	unsigned int currentScene = 0;
	
	Game game(&window, &multiplier);

	vector<Scene*> sceneManager;
	sceneManager.push_back(&game); // 0

	while (window.isOpen())
	{
		Event ev;
		while (window.pollEvent(ev))
		{
			switch (ev.type)
			{
			case Event::Closed:
				window.close();
				break;
			case Event::LostFocus:
				multiplier = 0;
				break;
			case Event::GainedFocus:
				multiplier = 1;
				break;
			default:
				break;
			}
		}

		// Update scene
		sceneManager.at(currentScene)->update();

		window.clear(Color(210, 210, 210));
		// Draw scene
		sceneManager.at(currentScene)->render();
		window.display();

	}
	return 0;
}