#include "Item.h"

Item::Item(Vector2f shapeSize, Vector2f startPos, Texture* item, float lf)
{
	died = false;
	lifetime = lf;

	shape.setSize(shapeSize);
	shape.setPosition(startPos);
	shape.setTexture(item);
}

void Item::update(float deltaTime)
{
	lifetime -= deltaTime;
	if (lifetime < 0)
	{
		died = true;
	}
}

void Item::drawOn(RenderWindow& window)
{
	window.draw(shape);
}
