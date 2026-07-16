#include "inventory.h"
#include "actor.h"



bool Inventory::addItem(std::unique_ptr<Item> item) {
	float newWeight = weight + item->getWeight();
	if (newWeight > owner->getWeightCapacity()) {
		return false;
	}
	weight = newWeight;
	items.push_back(std::move(item));
	return true;
}

void Inventory::removeItem(Item& item) {
	if (owner->getEquipment().isEquipped(&item)) {
		owner->getEquipment().unequip(&item);
	}
	
	auto it = std::find_if(items.begin(), items.end(), 
		[&](const std::unique_ptr<Item>& i) {
		return i.get() == &item;
	});

	// If the item is found, remove it from the inventory and update the weight
	if (it != items.end()) {
		weight -= (*it)->getWeight();
		items.erase(it);
	}
}

void Inventory::removeItemByIndex(size_t x, size_t q) {
	if (x >= items.size()) return;

	Item* item = items[x].get();
	item->setQuantity(item->getQuantity() - q);

	if (item->getQuantity() <= 0) {
		items.erase(items.begin() + x);
	}




}

