#pragma once
#include "FongFunc.h"

class Item
{
protected:
	RectangleShape shape;
	float lifetime;

public:
	bool died;

	Item(Vector2f shapeSize, Vector2f startPos, Texture* item, float lf);

	inline virtual FloatRect getGlobalBounds() { return shape.getGlobalBounds(); }
	inline virtual Vector2f getPosition() { return shape.getPosition(); }
	inline virtual void setPosition(Vector2f pos) { shape.setPosition(pos); }
	inline virtual void move(Vector2f offset) { shape.move(offset); }
	inline virtual void rotate(float angle) { shape.rotate(angle); }

	virtual void update(float deltaTime);
	virtual void drawOn(RenderWindow& window);
};