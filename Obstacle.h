#pragma once
#include "FongFunc.h"

class Obstacle
{
private:
	RectangleShape shape;

	Vector2f direction;
	Vector2f velocity;
	float speed;
	float lifetime;

public:
	bool died;

	Obstacle(Vector2f rectSize, Vector2f pos, float spd, Vector2f dir, float lt = 10);

	inline FloatRect getGlobalBounds() { return shape.getGlobalBounds(); }
	inline Vector2f getDirection() { return direction; }
	void update(float deltaTime);
	void drawOn(RenderWindow& window);
};