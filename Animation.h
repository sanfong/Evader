#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Animation
{
private:
	Vector2u imageCount;
	Vector2u currentImage;

	float totalTime;
	float switchTime;

public:
	IntRect uvRect;
	Texture* texture;

	Animation(Texture* texture, Vector2u imageCount, float switchTime);
	void updateTextureSize();

	void setSwitchTime(float switchTime);
	float getSwitchTime() { return switchTime; };

	void update(int row, float deltaTime);
};
