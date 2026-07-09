#include "animationLibrary.h"

const AnimationData& AnimationLibrary::get(const std::string& name) const{
	return data.at(name);
}

void AnimationLibrary::load(const std::string& name, const std::string& path) {
	json j = JsonLoader::load("assets/animations/" + path);
	data[name] = AnimationData::fromJson(j);
}