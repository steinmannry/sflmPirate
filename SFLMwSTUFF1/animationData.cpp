#include "animationData.h"
#include <iostream>
AnimationData AnimationData::fromJson(const json& j) {
	AnimationData data;

	data.textureName = j["texture"];
	data.frameWidth = j["frameWidth"];
	data.frameHeight = j["frameHeight"];
	data.frameCount = j["frames"];
	data.frameTime = j["frameTime"];
	data.row = j["row"];
	data.loop = j["loop"];
	data.reverse = j["reverse"];

	if (j.contains("sheetWidth")) data.sheetWidth = j["sheetWidth"];
	if (j.contains("sheetHeight")) data.sheetHeight = j["sheetHeight"];

	std::cout << "JSON keys: "
		<< j.dump(4)
		<< "\n";

	return data;
}