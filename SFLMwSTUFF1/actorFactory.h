#pragma once
#include <memory>
#include "actor.h"
#include "actorData.h"	

class ActorFactory {
public:
	static void loadDatabase(const json& j);
	static const ActorData& get(const std::string& id);
	static std::unique_ptr<Actor> create(const std::string& id, AnimationLibrary& animLib, TextureManager& tex);

	static std::unordered_map<std::string, ActorData> actorDB;
};