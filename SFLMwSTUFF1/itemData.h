#pragma once
#include <string>
#include "statsData.h"
#include "convert.h"
#include "attackPower.h"
#include "jsonLoader.h"
//#include "armorType.h"
//#include "effectEnum.h"


struct ItemData{
	ItemID id = ItemID::Unknown;
	std::string name;
	ItemType type = ItemType::Unknown;
	StatsData stats;
	float price = 1.f;
	float weight = 1.f;
	int itemPower = 0;
	AttackPower attackPower;	
	ArmorType armorType = ArmorType::Unknown;
	//Effect effect = Effect::None;
	//StateEffect stateEffect;

	static ItemData fromJson(const json& j);

	static ItemID convertID(const std::string& s);
	static ItemType convertItemType(const std::string& s);	
	static ArmorType convertArmorType(const std::string& s);
};