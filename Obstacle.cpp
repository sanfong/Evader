#include "Obstacle.h"

Obstacle::Obstacle(Vector2f rectSize, Vector2f pos, float spd, Vector2f dir, float lt)
{
	shape.setSize(rectSize);
	shape.setPosition(pos);
	shape.setFillColor(Color(randrange(0, 200), randrange(0, 200), randrange(0, 200)));
	speed = spd;
	lifetime = lt;
	direction = dir;
	died = false;
}

void Obstacle::update(float deltaTime)
{
	lifetime -= deltaTime;
	if (lifetime < 0)
		died = true;

	shape.move(normalize(direction) * speed * deltaTime);
}

void Obstacle::drawOn(RenderWindow& window)
{
	window.draw(shape);
}
