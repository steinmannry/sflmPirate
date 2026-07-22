#include "convert.h"

namespace Convert {

	static const std::unordered_map<std::string, ItemID> idMap = {
		{"StoneDagger", ItemID::StoneDagger},
		{"IronDagger", ItemID::IronDagger},
		{"ShortBow", ItemID::ShortBow},
		{"Tunic", ItemID::Tunic},
		{"LeatherArmor", ItemID::LeatherArmor},
		{"Herb", ItemID::Herb},
		{"WoodenArrows", ItemID::WoodenArrows}
		// Add more mappings here
	};

	ItemID itemID(const std::string& s) {
		if (auto it = idMap.find(s); it != idMap.end())  
			return it->second;
		
		return ItemID::Unknown;
	}

	static const std::unordered_map<std::string, ItemType> typeMap = {
		{"Weapon", ItemType::Weapon},
		{"Armor", ItemType::Armor},
		{"Consumable", ItemType::Consumable},
		{"Misc", ItemType::Misc}
	};

	ItemType itemType(const std::string& s) {
		if (auto it = typeMap.find(s); it != typeMap.end())  
			return it->second;
		return ItemType::Unknown;
	}

	static const std::unordered_map<std::string, ArmorType> armorMap = {
		{"Head", ArmorType::Head},
		{"Body", ArmorType::Body},
		{"Hands", ArmorType::Hands},
		{"Feet", ArmorType::Feet},
		{"Misc", ArmorType::Misc},
		{"Misc2", ArmorType::Misc2}
	};

	ArmorType armorType(const std::string& s) {
		if (auto it = armorMap.find(s); it != armorMap.end())  
			return it->second;
		return ArmorType::Unknown;
	}

	static const std::unordered_map<std::string, ItemEffect> itemEffectMap = {
		{"HealHP", ItemEffect::HealHP},
		{"HealMP", ItemEffect::HealMP},
		{"Stats", ItemEffect::Stats},
		{"ActorState", ItemEffect::ActorState},
		{"Unknown", ItemEffect::Unknown}
	};

	ItemEffect itemEffect(const std::string& s) {
		if (auto it = itemEffectMap.find(s); it != itemEffectMap.end())
			return it->second;
		return ItemEffect::Unknown;
	}
}