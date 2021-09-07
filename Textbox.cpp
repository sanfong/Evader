#include "Textbox.h"

constexpr int OFFRATIO = 3;

Textbox::Textbox()
{
	font = nullptr;
	align = Align::CENTER;
	charLimit = 0;
	offset = 0;
	xOffset = 0;
	isActive = false;
	isSelected = false;
	hasLimit = false;
	clickOutside = false;
}

Textbox::Textbox(Vector2f pos, Vector2f size, Color color, Font* font)
{
	this->font = font;
	text.setFont(*font);
	align = Align::CENTER;
	charLimit = 0;
	xOffset = 0;
	isActive = false;
	isSelected = false;
	hasLimit = false;
	clickOutside = false;

	shape.setPosition(pos);
	shape.setSize(size);
	shape.setFillColor(color);

	offset = this->text.getCharacterSize() / OFFRATIO;
	Vector2f textBoxSize = Vector2f(this->text.getGlobalBounds().width, this->text.getGlobalBounds().height);
	this->text.setPosition((shape.getSize() / 2.f) - (textBoxSize / 2.f) + (shape.getPosition()) + Vector2f(0, -offset));
}

void Textbox::setup(Vector2f pos, Vector2f size, Color color, Font* font)
{
	this->font = font;
	text.setFont(*font);

	shape.setPosition(pos);
	shape.setSize(size);
	shape.setFillColor(color);

	if (align == Align::CENTER)
	{
		offset = this->text.getCharacterSize() / OFFRATIO;
		Vector2f textBoxSize = Vector2f(this->text.getGlobalBounds().width, this->text.getGlobalBounds().height);
		this->text.setPosition((shape.getSize() / 2.f) - (textBoxSize / 2.f) + (shape.getPosition()) + Vector2f(0, -offset));
	}
	else if (align == Align::LEFT)
	{
		offset = this->text.getCharacterSize() / OFFRATIO;
		Vector2f textBoxSize = Vector2f(this->text.getGlobalBounds().width, this->text.getGlobalBounds().height);
		float y_pos = shape.getPosition().y + (shape.getSize().y / 2.f) - offset;
		this->text.setPosition(Vector2f(shape.getPosition().x + xOffset, y_pos));
	}
}

void Textbox::render(RenderWindow& window)
{
	window.draw(shape);
	window.draw(text);
}

void Textbox::setFontSize(int size)
{
	text.setCharacterSize(size);
}

void Textbox::setAlign(Align align)
{
	this->align = align;
}
