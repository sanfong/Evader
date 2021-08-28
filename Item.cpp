#include "Item.h"

Item::Item(Vector2f shapeSize, Vector2f startPos, Texture* item)
{
	shape.setSize(shapeSize);
	shape.setPosition(startPos);
	shape.setTexture(item);
}

void Item::update(float deltaTime)
{
}

void Item::drawOn(RenderWindow& window)
{
	window.draw(shape);
}
