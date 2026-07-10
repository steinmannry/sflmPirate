#include "sceneData.h"

SceneData SceneData::fromJson(const json& j) {
	SceneData data;

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

		if (j.contains("objects")) {
			for (auto& [key, ts] : j["objects"].items()) {
				ObjectData info;
				info.textureName = ts["texture"];
				info.tileWidth = ts["tileWidth"];
				info.tileHeight = ts["tileHeight"];
				info.variantCount = ts["variantCount"];
				info.collision = ts["collision"];
				info.eventType = parseEventType(ts.value("eventType", "None"));
				info.trigger = parseTriggerType(ts.value("trigger", "proximity"));
				info.targetScene = ts.value("targetScene", "");
				data.objects[key] = info;
			}
		}
		return data;
	}
}

MapType SceneData::parseMapType(const std::string& s) {
	if (s == "town") return MapType::Town;
	if (s == "overworld") return MapType::OverWorld;
	if (s == "battle") return MapType::Battle;

	return MapType::OverWorld; //default
}

EventType SceneData::parseEventType(const std::string& s) {
	if (s == "dialog") return EventType::Dialog;
	if (s == "sceneChange") return EventType::SceneChange;
	if (s == "loot") return EventType::Loot;
	if (s == "heal") return EventType::Heal;
	if (s == "statBoost") return EventType::StatBoost;
	if (s == "statPenalty") return EventType::StatPenalty;
	return EventType::None;
}

TriggerType SceneData::parseTriggerType(const std::string& s) {
	if (s == "proximity") return TriggerType::Proximity;
	if (s == "button") return TriggerType::Button;
	return TriggerType::Proximity; 
}
// OverWorld, Water, Town, Land, Battle, NauticalBattle };