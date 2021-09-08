#pragma once
#include "FongFunc.h"

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESC_KEY 27
constexpr int OFFRATIO = 3;

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
	string input;
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
	inline bool inputLogic(int ch)
	{
		if (ch == DELETE_KEY)
		{
			input = input.substr(0, input.length() - 1);
		}
		else if (ch == ENTER_KEY)
		{
			deselect();
			return true;
		}
		else if (ch == ESC_KEY)
		{
			deselect();
			return false;
		}
		else
		{
			input += static_cast<char>(ch);
		}
		text.setString(input + "_");
		return false;
	}

public:
	bool isActive;
	bool isSelected;
	bool hasLimit;

	Textbox();

	Textbox(Vector2f pos, Vector2f size, Font* font, Color textColor = Color(255, 255, 255), Color boxColor = Color(255, 255, 255));
	void setup(Vector2f pos, Vector2f size, Font* font, Color textColor = Color(255, 255, 255), Color boxColor = Color(255, 255, 255));

	void setFontSize(int size);
	void setAlign(Align align);
	inline void setXOffset(int off) { xOffset = off; }
	inline void setCharLimit(int limit) { charLimit = limit; }

	inline string getString() { return input; }
	inline RectangleShape& getShape() { return shape; }

	inline void deselect()
	{
		isSelected = false;
		text.setString(input + " ");
	}
	inline void select()
	{
		isSelected = true;
		text.setString(input + "_");
	}

	template <typename... Args>
	void update(Vector2f mousePos, void* funcAddress = nullptr, Args... args)
	{
		if (!isActive)
			return;

		bool leftClick = Mouse::isButtonPressed(Mouse::Left);
		if (leftClick && !shape.getGlobalBounds().contains(mousePos))
			clickOutside = true;
		else if (!leftClick)
			clickOutside = false;

		if (shape.getGlobalBounds().contains(mousePos) && !clickOutside && leftClick)
		{
			isSelected = true;
			text.setString(input + "_");
		}
		else if (clickOutside)
		{
			deselect();
		}

		for (size_t i = 0; i < textEvents.size() && isSelected; i++)
		{
			Event& ev = textEvents.at(i);
			// cout << textEvents.size() << endl;
			if (checkEventTextEntered(ev))
			{
				// cout << ev.text.unicode << endl;
				if ((hasLimit && input.length() < charLimit) || !hasLimit || ev.text.unicode == DELETE_KEY)
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
			Vector2f textBoxSize = Vector2f(text.getGlobalBounds().width, text.getGlobalBounds().height);
			text.setPosition((shape.getSize() / 2.f) - (textBoxSize / 2.f) + shape.getPosition() + Vector2f(offset, -offset));
		}
		else if (align == Align::LEFT)
		{
			Vector2f textBoxSize = Vector2f(this->text.getGlobalBounds().width, this->text.getGlobalBounds().height);
			float y_pos = shape.getPosition().y + (shape.getSize().y / 2.f) - (textBoxSize.y / 2.f) - offset;
			this->text.setPosition(Vector2f(shape.getPosition().x + xOffset, y_pos));
		}
	}

	template <typename TOwner, typename... Args>
	void update(Vector2f mousePos, TOwner* f, void(TOwner::* func)(Args...), Args... args)
	{
		if (!isActive)
			return;

		bool leftClick = Mouse::isButtonPressed(Mouse::Left);
		if (leftClick && !shape.getGlobalBounds().contains(mousePos))
			clickOutside = true;
		else if (!leftClick)
			clickOutside = false;

		if (shape.getGlobalBounds().contains(mousePos) && !clickOutside && leftClick)
		{
			isSelected = true;
			text.setString(input + "_");
		}
		else if (clickOutside)
		{
			deselect();
		}

		for (size_t i = 0; i < textEvents.size() && isSelected; i++)
		{
			Event& ev = textEvents.at(i);
			// cout << textEvents.size() << endl;
			if (checkEventTextEntered(ev))
			{
				// cout << ev.text.unicode << endl;
				if ((hasLimit && input.length() < charLimit) || !hasLimit || ev.text.unicode == DELETE_KEY)
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
			Vector2f textBoxSize = Vector2f(text.getGlobalBounds().width, text.getGlobalBounds().height);
			text.setPosition((shape.getSize() / 2.f) - (textBoxSize / 2.f) + shape.getPosition() + Vector2f(offset, -offset));
		}
		else if (align == Align::LEFT)
		{
			Vector2f textBoxSize = Vector2f(this->text.getGlobalBounds().width, this->text.getGlobalBounds().height);
			float y_pos = shape.getPosition().y + (shape.getSize().y / 2.f) - (textBoxSize.y / 2.f) - offset;
			this->text.setPosition(Vector2f(shape.getPosition().x + xOffset, y_pos));
		}
	}

	void render(RenderWindow& window);
}; 