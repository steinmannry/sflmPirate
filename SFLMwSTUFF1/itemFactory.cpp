#include "itemFactory.h"

std::unordered_map<ItemID, ItemData> ItemFactory::itemDB;

void ItemFactory::loadDatabase(const json& j) {
	for (auto& itemJson : j["items"]) {
		ItemData data = ItemData::fromJson(itemJson);	
		itemDB.emplace(data.id, ItemData::fromJson(itemJson));
	}
}

const ItemData& ItemFactory::get(ItemID id) {
	return itemDB.at(id);
}

std::unique_ptr<Item> ItemFactory::create(ItemID id) {
	const ItemData& d = itemDB.at(id);
	return std::make_unique<Item>(
		id,
		d.name,
		d.type,
		d.stats,
		d.price,
		d.weight,
		d.itemPower,
		d.attackPower,
		d.armorType
	);
}

