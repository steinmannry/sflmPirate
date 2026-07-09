#include "sceneData.h"

SceneData SceneData::fromJson(const json& j) {
	SceneData data;

	data.sceneName = j["sceneName"];
	data.mapType = SceneData::parseMapType(j["mapType"]);
	data.worldSize = vec2(j["worldSize"]);
	data.skyArea = areaFromJson(j["skyArea"]);
	data.groundArea = areaFromJson(j["groundArea"]);
	data.bottomOffset = areaFromJson(j["bottomOffset"]);

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
			obj.variantCount = inst.value("variant", 0);
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
// OverWorld, Water, Town, Land, Battle, NauticalBattle };