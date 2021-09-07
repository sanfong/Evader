#pragma once
#include "FongFunc.h"

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESC_KEY 27

enum class Align
{
	LEFT,
	CENTER
};

class Textbox
{
private:
	RectangleShape shape;
	Text text;
	bool clickOutside;
	int offset;
	int xOffset;
	Font* font;
	stringstream input;
	Align align;
	size_t charLimit;

	inline bool checkEventTextEntered(Event& ev)
	{
		if (ev.type == Event::TextEntered)
		{
			if (ev.text.unicode < 128)
			{
				return true;
			}
		}
		return false;
	}
	inline void deselect()
	{
		isSelected = false;
		text.setString(input.str());
	}
	inline bool inputLogic(int ch)
	{
		if (ch == DELETE_KEY)
		{
			if (input.str().length() > 0)
			{
				string currentStr = input.str();
				input.str(currentStr.substr(0, currentStr.length() - 1));
			}
		}
		else if (ch == ENTER_KEY)
		{
			return true;
		}
		else if (ch == ESC_KEY)
		{
			deselect();
		}
		else
		{
			input << static_cast<char>(ch);
		}
		text.setString(input.str() + "_");
		return false;
	}

public:
	bool isActive;
	bool isSelected;
	bool hasLimit;

	Textbox();

	Textbox(Vector2f pos, Vector2f size, Color color, Font* font);
	void setup(Vector2f pos, Vector2f size, Color color, Font* font);
	void setFontSize(int size);

	void setAlign(Align align);
	inline string getString() { return input.str(); }

	template <typename... Args>
	void update(Vector2f mousePos, void* funcAddress = nullptr, Args... args)
	{
		bool leftClick = Mouse::isButtonPressed(Mouse::Left);
		if (leftClick && !shape.getGlobalBounds().contains(mousePos))
			clickOutside = true;
		else if (!leftClick)
			clickOutside = false;

		if (shape.getGlobalBounds().contains(mousePos) && !clickOutside)
		{
			isSelected = true;
		}
		else if (clickOutside)
		{
			deselect();
		}

		for (size_t i = 0; i < events.size() && isSelected; i++)
		{
			Event& ev = events.at(i);
			if (checkEventTextEntered(ev))
			{
				if ((hasLimit && input.str().length() <= charLimit) || !hasLimit)
				{
					if (inputLogic(ev.text.unicode))
					{
						if (ev.text.unicode == ENTER_KEY && funcAddress != nullptr)
						{
							typedef void(*Function)(Args...);
							Function Fptr = (Function)funcAddress;
							Fptr(args...);
						}
					}
				}
			}
		}

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

	template <typename TOwner, typename... Args>
	void update(Vector2f mousePos, TOwner* f, void(TOwner::* func)(Args...), Args... args)
	{
		bool leftClick = Mouse::isButtonPressed(Mouse::Left);
		if (leftClick && !shape.getGlobalBounds().contains(mousePos))
			clickOutside = true;
		else if (!leftClick)
			clickOutside = false;

		if (shape.getGlobalBounds().contains(mousePos) && !clickOutside)
		{
			isSelected = true;
		}
		else if (clickOutside)
		{
			deselect();
		}

		for (size_t i = 0; i < events.size() && isSelected; i++)
		{
			Event& ev = events.at(i);
			if (checkEventTextEntered(ev))
			{
				if ((hasLimit && input.str().length() <= charLimit) || !hasLimit)
				{
					if (inputLogic(ev.text.unicode))
					{
						if (ev.text.unicode == ENTER_KEY)
						{
							(f->*func)(args...);
						}
					}
				}
			}
		}

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

	void render(RenderWindow& window);
};