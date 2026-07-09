#pragma once
#include <SFML/Graphics.hpp>



class Animation {
public:
	const sf::Texture* texture;

	int frameWidth = 0;
	int frameHeight = 0;
	int frameCount = 0;
	int row = 0;

	float frameTime = 0.f;
	float timer = 0.f;

	int currentFrame = 0;
	bool loop = true;
	bool reverse = false;

	Animation() = default;
	Animation(const sf::Texture* tex, int fw, int fh,
		int count, float time, int rowIndex = 0, bool shouldLoop = true, bool shouldReverse = false)
		: texture(tex), frameWidth(fw), frameHeight(fh), frameCount(count),
		frameTime(time), row(rowIndex), loop(shouldLoop), reverse(shouldReverse){
	}
};