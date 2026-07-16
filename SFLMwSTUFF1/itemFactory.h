#pragma once
#include <string>	
#include <unordered_map>
#include <memory>
#include "item.h"
#include "itemData.h"
#include "itemID.h"


class ItemFactory {
public:
	static void loadDatabase(const json& j);
	static const ItemData& get(ItemID id);
	static std::unique_ptr<Item> create(ItemID id);

	static std::unordered_map<ItemID, ItemData> itemDB;

};