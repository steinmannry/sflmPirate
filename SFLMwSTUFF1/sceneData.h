#pragma once
#include <SFML/Graphics.hpp>
#include "area.h"
#include <string>
#include "jsonLoader.h"

enum class MapType {OverWorld, Water, Town, Land, Battle, NauticalBattle};
enum class EventType {None, Dialog, SceneChange, Loot, Heal, StatBoost, StatPenalty, Tree};
enum class TriggerType {Proximity, Button, Command};

struct TilesetInfo {
	std::string textureName;
	int tileWidth;
	int tileHeight;
};

struct ObjectInstance {
	std::string type;
	int variant;
	float x;
	float y;	
};

struct ObjectData {
	std::string textureName;
	int tileWidth;
	int tileHeight;
	int variantCount;
	bool collision = false;
	sf::FloatRect collisionBox;
	EventType eventType = EventType::None;
	TriggerType trigger = TriggerType::Proximity;
	std::string targetScene;
};

struct GradientData {
	bool enabled = false;
	sf::Color topLeft;
	sf::Color topRight;
	sf::Color bottomLeft;
	sf::Color bottomRight;
};

struct SceneData {
	std::string sceneName;
	MapType mapType;
	sf::Vector2f worldSize;
	Area skyArea;
	Area groundArea;
	Area bottomOffset;
	GradientData skyGradient;
	GradientData groundGradient;
	sf::Vector2f spawnPos;

	//std::unordered_map<std::string, TilesetInfo> tilesets;

	std::unordered_map<std::string, ObjectData> objects;
	std::vector<ObjectInstance> objectInstances;


	static SceneData fromJson(const json& j);

	static sf::Vector2f vec2(const json& j) {
		return sf::Vector2f(j["x"], j["y"]);
	}

	static sf::Color colorFromArray(const json& j) {
		return sf::Color(j[0], j[1], j[2]);
	}

	static Area areaFromJson(const json& j) {
		Area a;
		a.topLeft = vec2(j["topLeft"]);
		a.bottomRight = vec2(j["bottomRight"]);
		return a;
	}

	static MapType parseMapType(const std::string& s);
	static EventType parseEventType(const std::string& s);
	static TriggerType parseTriggerType(const std::string& s);
	//wind struct
	//paralax
	//player and enemy spawn pos's
};