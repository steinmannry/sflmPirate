#pragma once
#include <string>
#include <unordered_map>
#include "itemEffect.h"
#include "itemID.h"
#include "itemType.h"
#include "armorType.h"

namespace Convert {
	ItemID itemID(const std::string& s);
	ItemType itemType(const std::string& s);
	ArmorType armorType(const std::string& s);
	ItemEffect itemEffect(const std::string& s);
}