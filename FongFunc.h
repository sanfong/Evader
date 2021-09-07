#pragma once
#include <iostream>
#include <time.h>
#include <vector>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "LeaderBoard.h"

#define SCREEN_SIZE 800
#define SCREEN_HALF 400

using namespace sf;

extern float multiplier;
extern int currentScene;
extern vector<Event> events;

Vector2f normalize(Vector2f vec);

float distance(Vector2f a, Vector2f b);

float vectorLength(Vector2f vec);

bool isCollided(RectangleShape a, RectangleShape b);

int randrange(int start, int stop);

// return true if success else false
// p is in [0, 100]
bool chance(int p);

inline void changeScene(int i)
{
	currentScene = i;
}

template<typename Num = float>
inline Num clamp(Num value, Num min, Num max)
{
	if (value > max)
		value = max;

	if (value < min)
		value = min;

	return value;
}