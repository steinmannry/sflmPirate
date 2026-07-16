#include "itemData.h"
#include <iostream>

ItemData ItemData::fromJson(const json& j) {
	ItemData data;

	try {
		data.id = Convert::itemID(j["id"]);
		data.name = j["name"];
		data.type = Convert::itemType(j["type"]);

		if (j.contains("stats")) {
			auto& js = j["stats"];
			if (js.contains("maxHP")) data.stats.maxHP = (js["maxHP"]);
			if (js.contains("maxMP")) data.stats.maxMP = (js["maxMP"]);
			if (js.contains("STR")) data.stats.STR = (js["STR"]);
			if (js.contains("INT")) data.stats.INT = (js["INT"]);
			if (js.contains("DEX")) data.stats.DEX = (js["DEX"]);
			if (js.contains("CON")) data.stats.CON = (js["CON"]);
			if (js.contains("CHA")) data.stats.CHA = (js["CHA"]);
			if (js.contains("LUK")) data.stats.LUK = (js["LUK"]);
			if (js.contains("DEF")) data.stats.DEF = (js["DEF"]);
			if (js.contains("SPD")) data.stats.SPD = (js["SPD"]);
		}

		data.price = j.value("price", 0.f);
		data.weight = j.value("weight", .1f);
		data.itemPower = j.value("itemPower", 0.f);


		if (j.contains("attackPower")) {
			data.attackPower.minDamage = j["attackPower"]["min"];
			data.attackPower.maxDamage = j["attackPower"]["max"];
		}

		data.armorType = Convert::armorType(j.value("armorType", "Misc"));

		
	}
	catch (const std::exception& e) {
		std::cout << "error loading time: " << j.dump(4) << "\n";
		std::cout << "exception: " << e.what() << "\n";
	}

	return data;
}

