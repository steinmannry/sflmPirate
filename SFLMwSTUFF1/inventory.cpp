#include "inventory.h"
#include "actor.h"
#include <iostream>


bool Inventory::addItem(std::unique_ptr<Item> item, int q) {
	int quantityToPlace = q;
	float totalWeight = item->getWeight() * quantityToPlace;
	while (totalWeight + weight > owner->getWeightCapacity()) {
		--quantityToPlace;

		if (quantityToPlace < 1) {
			return false;
		}
		totalWeight = item->getWeight() * quantityToPlace;
	}	
	
	for (auto& i : items) {
		if (i.get()->getID() == item.get()->getID()) {
			i.get()->setQuantity(i.get()->getQuantity() + quantityToPlace);
			weight += totalWeight;
			return true;
		}	
	}

	item->setQuantity(quantityToPlace);
	items.push_back(std::move(item));
	weight += totalWeight;
	return true;
}

std::unique_ptr<Item> Inventory::extractItem(int index) {
	Item* item = items[index].get();
	
	weight -= item->getWeight();
	if (item->getQuantity() == 1) {
		std::unique_ptr<Item> ptr = std::move(items[index]);
		items.erase(items.begin() + index);
		return ptr;
	}

	//more than one in stack
	item->setQuantity(item->getQuantity() -1);
	std::unique_ptr<Item> newItem = std::make_unique<Item>(*item);
	newItem->setQuantity(1);
	std::cout << "removing itemfrom stack\n";
	return newItem;
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
	weight -= item->getWeight() * q;

	if (item->getQuantity() <= 0) {
		items.erase(items.begin() + x);
	}

}

void Inventory::useItem(size_t x) {
	if (x >= items.size()) return;

	Item* item = items[x].get();
	ItemEffect ie = item->getItemEffect();
	switch (ie) {
	case ItemEffect::HealHP:
		owner->setHP(item->getItemPower());
		removeItemByIndex(x, 1);
		std::cout << " you healed many hp's\n";
		break;
	case ItemEffect::HealMP:
		owner->setMP(item->getItemPower());
		removeItemByIndex(x, 1);
		break;
	case ItemEffect::Stats:
		//do stuff
		break;
	}
}
