#pragma once
#include "FongFunc.h"

using namespace sf;
using namespace std;

class Scene
{
protected:
	RenderWindow* window;

public:
	inline Scene() { window = nullptr; }

	virtual void update();
	virtual void render();
};