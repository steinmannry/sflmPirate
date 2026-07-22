#include "sceneData.h"
#include <iostream>

SceneData SceneData::fromJson(const json& j) {
	SceneData data;

	try {
		data.sceneName = j["sceneName"];
		data.mapType = SceneData::parseMapType(j["mapType"]);
		data.worldSize = vec2(j["worldSize"]);
		data.skyArea = areaFromJson(j["skyArea"]);
		data.groundArea = areaFromJson(j["groundArea"]);
		data.bottomOffset = areaFromJson(j["bottomOffset"]);

		if (j.contains("spawnPos")) {
			data.spawnPos.x = j["spawnPos"]["x"];
			data.spawnPos.y = j["spawnPos"]["y"];
		}

		if (j.contains("enemies")) {
			for (auto& s : j["enemies"]) {
				BattleSpawn bs;
				bs.id = s["id"];
				bs.position.x = s["x"];
				bs.position.y = s["y"];
				data.enemies.push_back(bs);
			}
		}

		if (j.contains("skyGradient")) {
			const auto& sg = j["skyGradient"];
			data.skyGradient.enabled = sg.value("enabled", false);
			if (data.skyGradient.enabled) {
				data.skyGradient.topLeft = colorFromArray(sg["topLeft"]);
				data.skyGradient.topRight = colorFromArray(sg["topRight"]);
				data.skyGradient.bottomLeft = colorFromArray(sg["bottomLeft"]);
				data.skyGradient.bottomRight = colorFromArray(sg["bottomRight"]);
			}
		}

		if (j.contains("groundGradient")) {
			const auto& gg = j["groundGradient"];
			data.groundGradient.enabled = gg.value("enabled", false);
			if (data.groundGradient.enabled) {
				data.groundGradient.topLeft = colorFromArray(gg["topLeft"]);
				data.groundGradient.topRight = colorFromArray(gg["topRight"]);
				data.groundGradient.bottomLeft = colorFromArray(gg["bottomLeft"]);
				data.groundGradient.bottomRight = colorFromArray(gg["bottomRight"]);
			}
		}

		/*if (j.contains("tilesets")) {
			for (auto& [key, ts] : j["tilesets"].items()) {
				TilesetInfo info;
				info.textureName = ts["texture"];
				info.tileWidth = ts["tileWidth"];
				info.tileHeight = ts["tileHeight"];
				data.tilesets[key] = info;
			}
		}*/

		if (j.contains("objectInstances")) {
			for (auto& inst : j["objectInstances"]) {
				ObjectInstance obj;
				obj.type = inst["type"];
				obj.variant = inst.value("variant", 0);
				obj.x = inst["x"];
				obj.y = inst["y"];
				data.objectInstances.push_back(obj);
			}
		}

		if (j.contains("objects")) {
			for (auto& [key, obj] : j["objects"].items()) {
				ObjectData info;
				info.textureName = obj["texture"];
				info.tileWidth = obj["tileWidth"];
				info.tileHeight = obj["tileHeight"];
				info.variantCount = obj["variantCount"];

				if (obj.contains("collision")) {
					info.collision = obj["collision"];
				}
				if (obj.contains("collisionBox")){
					auto& cb = obj["collisionBox"];
					info.collisionBox = sf::FloatRect(
						cb["left"],
						cb["top"],
						cb["width"],
						cb["height"]
					);
				}
				info.eventType = parseEventType(obj.value("eventType", "None"));
				info.trigger = parseTriggerType(obj.value("triggerType", "Proximity"));
				info.targetScene = obj.value("targetScene", "");
				data.objects[key] = info;
			}
		}
	}
		catch (const std::exception& e) {
			std::cout << "sceneData error: " << e.what() << "\n";
		}
	
		return data;	
}

MapType SceneData::parseMapType(const std::string& s) {
	if (s == "Town") return MapType::Town;
	if (s == "Overworld") return MapType::OverWorld;
	if (s == "Battle") return MapType::Battle;

	return MapType::OverWorld; //default
}

EventType SceneData::parseEventType(const std::string& s) {
	if (s == "Dialog") return EventType::Dialog;
	if (s == "SceneChange") return EventType::SceneChange;
	if (s == "Loot") return EventType::Loot;
	if (s == "Heal") return EventType::Heal;
	if (s == "StatBoost") return EventType::StatBoost;
	if (s == "StatPenalty") return EventType::StatPenalty;
	if (s == "Tree") return EventType::Tree;
	return EventType::None;
}

TriggerType SceneData::parseTriggerType(const std::string& s) {
	if (s == "Proximity") return TriggerType::Proximity;
	if (s == "Button") return TriggerType::Button;
	if (s == "Command") return TriggerType::Command;
	return TriggerType::Proximity; 
}
// OverWorld, Water, Town, Land, Battle, NauticalBattle };