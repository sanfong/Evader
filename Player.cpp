#include "Player.h"
#include "Animation.h"
#include "FongFunc.h"
#include <iostream>

using namespace sf;
using namespace std;

Player::Player(Vector2f shapeSize, Vector2f startPos, float speed, Texture* texture, Vector2u imageCount, float switchTime, RenderWindow* win) :
	animation(texture, imageCount, switchTime)
{
	window = win;
	this->speed = speed;
	row = 0;

	spdUpDuration = 0;
	speedUp = speed * 2.f;

	shape.setSize(shapeSize);
	shape.setPosition(startPos);
	shape.setTexture(texture);
	shape.setOrigin(shapeSize / 2.f);
}

Animation& Player::thisAnimation()
{
	return animation;
}

void Player::setWindowPtr(RenderWindow* window)
{
	this->window = window;
}

void boundary(RectangleShape& shape)
{
	Vector2f position = shape.getPosition();
	Vector2f halfSize = shape.getSize() / 2.f;
	if (position.x < halfSize.x)
	{
		shape.setPosition(halfSize.x, position.y);
		position = shape.getPosition();
	}
	if (position.x > 800 - halfSize.x)
	{
		shape.setPosition(800 - halfSize.x, position.y);
		position = shape.getPosition();
	}
	if (position.y < halfSize.y)
	{
		shape.setPosition(position.x, halfSize.y);
		position = shape.getPosition();
	}
	if (position.y > 800 - halfSize.y)
	{
		shape.setPosition(position.x, 800 - halfSize.y);
		position = shape.getPosition();
	}
}

void Player::update(float deltaTime)
{
	velocity = Vector2f(0, 0);
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		velocity.y = -1;
		row = 3;
	}
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		velocity.x = -1;
		row = 2;
	}
	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		velocity.y = 1;
		row = 0;
	}
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		velocity.x = 1;
		row = 1;
	}

	if (spdUpDuration > 0)
	{
		spdUpDuration -= deltaTime;
		velocity = normalize(velocity) * speedUp * deltaTime;
	}
	else
	{
		velocity = normalize(velocity) * speed * deltaTime;
	}
	shape.move(velocity);

	boundary(shape);
	
	if (velocity == Vector2f(0, 0))
	{
		switch (row)
		{
		case 0:
			row = 4;
			break;
		case 1:
			row = 5;
			break;
		case 2:
			row = 6;
			break;
		case 3:
			row = 7;
			break;
		default:
			break;
		}
	}

	animation.update(row, deltaTime);
	shape.setTextureRect(animation.uvRect);
}

void Player::drawOn(RenderWindow& window)
{
	window.draw(shape);
}
