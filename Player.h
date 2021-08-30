#pragma once
#include "Animation.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class Player
{
private:
	RectangleShape shape;
	Animation animation;
	RenderWindow* window;
	
	Vector2f velocity;
	float speed;
	int row;

	float speedUp;
	float spdUpDuration;

public:
	Player(Vector2f shapeSize, Vector2f startPos, float speed, Texture* texture, Vector2u imageCount, float switchTime, RenderWindow* win = nullptr);

	Animation& thisAnimation();
	inline FloatRect getGlobalBounds() { return shape.getGlobalBounds(); }
	inline Vector2f getPosition() { return shape.getPosition(); }
	inline void setPosition(Vector2f pos) { shape.setPosition(pos); }
	inline void move(Vector2f offset) { shape.move(offset); }
	inline void rotate(float angle) { shape.rotate(angle); }
	
	inline void setBoost(float sec) { spdUpDuration = sec; }
	void setWindowPtr(RenderWindow* window);
	void update(float deltaTime);
	void drawOn(RenderWindow& window);
};