#pragma once
#include <vector>
#include <string>
#include "armorType.h"

class Item;
class Actor;

class Equipment{
public:
	void equip(Item* item);
	void unequip(Item* item);

	void setOwner(Actor* a) { owner = a; }
	Item* getWeapon() const { return weapon; }
	Item* getBody() const { return armor; }
	Item* getHead() const { return head; }
	Item* getFeet() const { return feet; }
	Item* getHands() const { return hands; }
	Item* getMisc() const { return misc; }
	//Stats getTotalBonus() const;
	bool isEquipped(const Item* item) const;

	std::vector<std::pair<std::string, Item*>> getEquippedList() const;

private:
	Actor* owner = nullptr;

	Item* weapon = nullptr;

	Item* head = nullptr;
	Item* armor = nullptr;
	Item* hands = nullptr;
	Item* feet = nullptr;
	Item* misc = nullptr;
	Item* misc2 = nullptr;
};