#include "FongFunc.h"
#include "Scene.h"
#include "Game.h"
#include "Menu.h"

using namespace sf;
using namespace std;

float multiplier = 1;
int currentScene = 0;
vector<Event> textEvents = {};

int main()
{
	RenderWindow window(VideoMode(800, 800), "Game", Style::Close);
	window.setVerticalSyncEnabled(true);
	srand(time(static_cast<time_t*>(0)));
	Game game(&window);
	Menu menu(&window, &game);
	
	vector<Scene*> sceneManager;
	sceneManager.push_back(&menu); // 0
	sceneManager.push_back(&game); // 1

	while (window.isOpen())
	{
		textEvents.clear();
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
			case Event::TextEntered:
				textEvents.push_back(ev);
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