#include "Button.h"

using namespace sf;
using namespace std;

const int OFFRATIO = 3;

Button::Button()
{
	this->font = nullptr;
}

Button::Button(Vector2f position, Vector2f size, Font* font, string text, Color idle, Color hover, Color active)
{
	shape.setPosition(position);
	shape.setSize(size);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(Color::White);
	this->text.setCharacterSize(24);

	offset = this->text.getCharacterSize() / OFFRATIO;
	Vector2f textBoxSize = Vector2f(this->text.getGlobalBounds().width, this->text.getGlobalBounds().height);
	this->text.setPosition((shape.getSize() / 2.f) - (textBoxSize / 2.f) + (shape.getPosition()) + Vector2f(0, -offset));

	this->idle = idle;
	this->hover = hover;
	this->active = active;

	shape.setFillColor(this->idle);
}

void Button::setup(Vector2f position, Vector2f size, Font* font, string text, Color idle, Color hover, Color active)
{
	shape.setPosition(position);
	shape.setSize(size);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(Color::White);
	this->text.setCharacterSize(24);

	offset = this->text.getCharacterSize() / OFFRATIO;
	Vector2f textBoxSize = Vector2f(this->text.getGlobalBounds().width, this->text.getGlobalBounds().height);
	this->text.setPosition((shape.getSize() / 2.f) - (textBoxSize / 2.f) + (shape.getPosition()) + Vector2f(0, -offset));

	this->idle = idle;
	this->hover = hover;
	this->active = active;

	shape.setFillColor(this->idle);
}

void Button::update(Vector2f mousePos)
{
	state = buttonState::IDLE;
	if (shape.getGlobalBounds().contains(mousePos))
	{
		state = buttonState::HOVER;
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			state = buttonState::ACTIVE;
		}
	}

	switch (state)
	{
	case buttonState::IDLE:
		shape.setFillColor(idle);
		break;
	case buttonState::HOVER:
		shape.setFillColor(hover);
		break;
	case buttonState::ACTIVE:
		shape.setFillColor(active);
		break;
	default:
		cout << "State Error" << endl;
		break;
	}
}

void Button::render(RenderWindow& window)
{
	window.draw(shape);
	window.draw(text);
}

bool Button::isPressed()
{
	if (state == buttonState::ACTIVE)
	{
		return true;
	}
	return false;
}

buttonState Button::getButtonState()
{
	return state;
}

void Button::setText(string text)
{
	this->text.setString(text);
	Vector2f textBoxSize = Vector2f(this->text.getGlobalBounds().width, this->text.getGlobalBounds().height);
	this->text.setPosition((shape.getSize() / 2.f) - (textBoxSize / 2.f) + (shape.getPosition()) + Vector2f(0, -offset));
}

string Button::getText()
{
	return text.getString();
}

void Button::setFont(Font* font)
{
	this->text.setFont(*this->font);
	Vector2f textBoxSize = Vector2f(this->text.getGlobalBounds().width, this->text.getGlobalBounds().height);
	this->text.setPosition((shape.getSize() / 2.f) - (textBoxSize / 2.f) + (shape.getPosition()) + Vector2f(0, -offset));
}

const Font* Button::getFont()
{
	return text.getFont();
}

void Button::setFontSize(unsigned int size)
{
	text.setCharacterSize(size);
	offset = size / OFFRATIO;
	Vector2f textBoxSize = Vector2f(this->text.getGlobalBounds().width, this->text.getGlobalBounds().height);
	this->text.setPosition((shape.getSize() / 2.f) - (textBoxSize / 2.f) + (shape.getPosition()) + Vector2f(0, -offset));
}

unsigned int Button::getFontSize()
{
	return text.getCharacterSize();
}

void Button::increaseFontSizeBy(int size)
{
	setFontSize(text.getCharacterSize() + size);
}