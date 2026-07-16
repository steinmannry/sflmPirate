#include "equipment.h"
#include "item.h"

void Equipment::equip(Item* item) {
	if (item->getType() != ItemType::Armor && item->getType() != ItemType::Weapon)
		return;

	if (item->getType() == ItemType::Weapon) {
		weapon = item;
		return;
	}

	if (item->getType() == ItemType::Armor) {
		switch (item->getArmorType()) {
		case ArmorType::Head:
			head = item;
			break;

		case ArmorType::Body:
			armor = item;
			break;

		case ArmorType::Hands:
			hands = item;
			break;

		case ArmorType::Feet:
			feet = item;
			break;

		case ArmorType::Misc:
			if (!misc)
				misc = item;
			else
				misc2 = item;
			break;
		default:
			break;
		}
	}
}

void Equipment::unequip(Item* item) {
	if (item->getType() == ItemType::Weapon) {
		if (weapon == item)
			weapon = nullptr;
	}
	switch (item->getArmorType()) {
		case ArmorType::Head:
			if (head == item)
				head = nullptr;
			break;
		case ArmorType::Body:
			if (armor == item)
				armor = nullptr;
			break;
		case ArmorType::Hands:
			if (hands == item)
				hands = nullptr;
			break;
		case ArmorType::Feet:
			if (feet == item)
				feet = nullptr;
			break;
		case ArmorType::Misc:
			if (misc == item)
				misc = nullptr;
			else if (misc2 == item)
				misc2 = nullptr;
			break;
		default:
			break;
	}
}

bool Equipment::isEquipped(const Item* item) const {
	return (item == weapon || item == head || item == armor || item == hands || item == feet || item == misc || item == misc2);
}

std::vector<std::pair<std::string, Item*>> Equipment::getEquippedList() const {
	std::vector<std::pair<std::string, Item*>> list;

	list.emplace_back("Weapon", weapon);
	list.emplace_back("Armor", armor);
	list.emplace_back("Head", head);
	list.emplace_back("Hands", hands);
	list.emplace_back("Feet", feet);
	list.emplace_back("Misc", misc);
	list.emplace_back("Misc2", misc2);

	return list;
}