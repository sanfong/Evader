#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

// contain IDLE, HOVER, and ACTIVE
enum class buttonState
{
	IDLE,
	HOVER,
	ACTIVE
};

// Clickable button with ability to callback
class Button
{
private:
	RectangleShape shape;
	RectangleShape box;
	Font* font = NULL;
	Text text;

	Color idle;
	Color hover;
	Color active;

	buttonState state = buttonState::IDLE;
	int offset = 0;

public:
	Button();
	/// <summary>Constructor of Button class</summary>
	/// <param name="position">: Position of the button (top-left)</param>
	/// <param name="size">: Size of the button</param>
	/// <param name="font">: font pointer</param>
	/// <param name="text">: dunno what to say about. It's just button text.</param>
	/// <param name="idle">: Color when idle</param>
	/// <param name="hover">: Color when mouse is above the button</param>
	/// <param name="active">: Color when mouse clicked the button</param>
	Button(Vector2f position, Vector2f size, Font* font, string text, Color idle, Color hover, Color active);

	void setup(Vector2f position, Vector2f size, Font* font, string text, Color idle, Color hover, Color active);

	/// <summary>Normal update</summary>
	/// <param name="position">: Position of the button (top-left)</param>
	void update(Vector2f mousePos);

	// draw the button on the window
	void render(RenderWindow& window);

	// return true if the button is pressed, false otherwise
	bool isPressed();

	// use if necessary
	// return state of the button
	// 3 states were IDLE, HOVER, and ACTIVE
	buttonState getButtonState();

	// set text of the button
	void setText(string text);
	// return text of the button as string
	string getText();

	// Self-explanatory
	void setFont(Font* font);
	// Self-explanatory
	const Font* getFont();
	// self-explanatory
	void setFontSize(unsigned int size);
	// Self-explanatory
	unsigned int getFontSize();
	// Same as button.setFontSize(button.getFontSize() + size);
	void increaseFontSizeBy(int size);

	/*
	update with an ability to callback
	Recommended if you want to use the callback ability
	How to use:
	* update<parameter type of callback function...>(mousePos, funcAddress, parameter of callback function...);
	* update<string, int>(mousePos, PrintNameAge, "User", 18);
	* update(mousePos, changePage);
	*/
	template <typename... Args>
	void update(Vector2f mousePos, void* funcAddress = nullptr, Args... args)
	{
		static bool once = true;
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
			once = true;
			break;
		case buttonState::HOVER:
			shape.setFillColor(hover);
			once = true;
			break;
		case buttonState::ACTIVE:
			shape.setFillColor(active);
			if (funcAddress != nullptr && once)
			{
				once = false;
				typedef void(*Function)(Args...);
				Function Fptr = (Function)funcAddress;
				Fptr(args...);
			}
			break;
		default:
			cout << "State Error" << endl;
			break;
		}
	}
	
	// for callback member function with no argument
	// <Class, Member-func>(mousePos, Obj-pointer)
	template <typename TOwner, void(TOwner::* func)()>
	void update(Vector2f mousePos, TOwner* f)
	{
		static bool once = true;
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
			once = true;
			break;
		case buttonState::HOVER:
			shape.setFillColor(hover);
			once = true;
			break;
		case buttonState::ACTIVE:
			shape.setFillColor(active);
			if (f != nullptr && once)
			{
				once = false;
				(f->*func)();
			}
			break;
		default:
			cout << "State Error" << endl;
			break;
		}
	}

	// for callback member function with one argument
	// <Class, Argument-type, Member-func>(mousePos, Obj-pointer, arg)
	template <typename TOwner, typename Arg, void(TOwner::* func)(Arg)>
	void update(Vector2f mousePos, TOwner* f, Arg arg)
	{
		static bool once = true;
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
			once = true;
			break;
		case buttonState::HOVER:
			shape.setFillColor(hover);
			once = true;
			break;
		case buttonState::ACTIVE:
			shape.setFillColor(active);
			if (f != nullptr && once)
			{
				once = false;
				(f->*func)(arg);
			}
			break;
		default:
			cout << "State Error" << endl;
			break;
		}
	}

	// for callback member function with two arguments
	// <Class, Argument-type1, Argument-type2, Member-func>(mousePos, Obj-pointer, arg1, arg2)
	template <typename TOwner, typename Arg1, typename Arg2, void(TOwner::* func)(Arg1, Arg2)>
	void update(Vector2f mousePos, TOwner* f, Arg1 arg1, Arg2 arg2)
	{
		static bool once = true;
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
			once = true;
			break;
		case buttonState::HOVER:
			shape.setFillColor(hover);
			once = true;
			break;
		case buttonState::ACTIVE:
			shape.setFillColor(active);
			if (f != nullptr && once)
			{
				once = false;
				(f->*func)(arg1, arg2);
			}
			break;
		default:
			cout << "State Error" << endl;
			break;
		}
	}
};