#pragma once
#include <iostream>
#include <time.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace sf;

Vector2f normalize(Vector2f vec);

float distance(Vector2f a, Vector2f b);

float vectorLength(Vector2f vec);

bool isCollided(RectangleShape a, RectangleShape b);

int randrange(int start, int stop);

template<typename Num = float>
inline Num clamp(Num value, Num min, Num max)
{
	if (value > max)
		value = max;

	if (value < min)
		value = min;

	return value;
}