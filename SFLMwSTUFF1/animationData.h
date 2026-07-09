#pragma once
#include <string>
#include "jsonLoader.h"

class AnimationData {
public:
	std::string textureName;
	int frameWidth;
	int frameHeight;
	int frameCount;
	float frameTime;
	int row;
	bool loop;
	bool reverse;

	int sheetWidth;
	int sheetHeight;

	static AnimationData fromJson(const json& j);
};