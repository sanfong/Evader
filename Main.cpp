#include "FongFunc.h"
#include "Scene.h"
#include "Game.h"

using namespace sf;
using namespace std;

int main()
{
    RenderWindow window(VideoMode(800, 800), "Game", Style::Close);
    window.setFramerateLimit(60);

    srand(time(NULL));
    unsigned int currentScene = 0;
    
    Game game(&window);

    vector<Scene*> sceneManager;
    sceneManager.push_back(&game); // 0

    while (window.isOpen())
    {
        Event ev;
        while (window.pollEvent(ev))
        {
            if (ev.type == Event::Closed)
                window.close();
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