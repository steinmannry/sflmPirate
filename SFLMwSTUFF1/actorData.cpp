#include "actorData.h"
#include <iostream>
#include "parseStatsMode.h"

ActorData ActorData::fromJson(const json& j) {
	ActorData data;

	try {
		data.id = j["id"];
		data.name = j["name"];
		data.className = j["className"];
		data.texture = j["texture"];
		std::cout << "Animations JSON field: " << j["animations"].dump(4) << "\n";

		for (auto& animID : j["animations"]) {
			data.animations.push_back(animID);
		}

		if (j.contains("statsMode")) {
			std::string modeStr = j["statsMode"];
			data.statsMode = parseStatsMode(modeStr);
		}

		data.level = j["level"];
		if (j.contains("stats")) {
			const auto& s = j["stats"];
			data.stats.maxHP = s["maxHP"];
			data.stats.maxMP = s["maxMP"];
			data.stats.STR = s["STR"];
			data.stats.INT = s["INT"];
			data.stats.DEX = s["DEX"];
			data.stats.CON = s["CON"];
			data.stats.CHA = s["CHA"];
			data.stats.LUK = s["LUK"];
			data.stats.DEF = s["DEF"];
			data.stats.SPD = s["SPD"];
		}
		if (j.contains("equipment")) {
			const auto& e = j["equipment"];
			data.equipment.weapon = e.value("weapon", "");
			data.equipment.armor = e.value("armor", "");
			data.equipment.head = e.value("head", "");
			data.equipment.hands = e.value("hands", "");
			data.equipment.feet = e.value("feet", "");
			data.equipment.misc = e.value("misc", "");
		}

		if (j.contains("inventory")) {
			for (auto& itemJson : j["inventory"]) {
				InventoryEntry entry;
				entry.id = itemJson["id"];
				entry.quantity = itemJson.value("quantity", 1);
				data.inventory.entries.push_back(entry);
			}
		}
	}
	catch (const std::exception& e) {
		std::cout << "error loading time: " << j.dump(4) << "\n";
		std::cout << "exception: " << e.what() << "\n";
	}

	return data;
}
