#pragma once
#include <string>
#include "statsData.h"
#include "itemData.h"
#include "itemID.h"
#include "itemType.h"
#include "armorType.h"
#include "attackPower.h"

class Actor;


class Item
{
public:
	Item(ItemID id, const std::string& n, ItemType t, const StatsData sd, float p, float w, int pow, AttackPower ap, ArmorType at);

	void setQuantity(int x) { quantity = x; }
	const int getQuantity() const { return quantity; }
	ItemID getID() const { return id; }
	const std::string& getName() const { return name; }
	ItemType getType() const { return type; }
	ArmorType getArmorType() const { return armorType; }
	const StatsData& getStats() const { return bonusStats; }
	float getPrice() const { return price; }
	float getWeight() const { return weight; }
	int getItemPower() const { return itemPower; }

	//Effect getEffect() const { return effect; }
	//StateEffect getStateEffect() const { return se; }

private:
	ItemID id;
	std::string name;
	ItemType type;
	StatsData bonusStats;
	float price;
	float weight;	
	int quantity = 1;
	int itemPower;
	AttackPower attackPower;
	ArmorType armorType;
	//Effect effect;
	//StateEffect se;

};