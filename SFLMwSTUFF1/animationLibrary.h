#pragma once
#include <string>
#include "animationData.h"

class AnimationLibrary {
public:
	void load(const std::string& name, const std::string& file);
	const AnimationData& get(const std::string& name) const;

private:
	std::unordered_map<std::string, AnimationData> data;
};