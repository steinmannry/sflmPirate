#pragma once
#include <string>
#include "itemEffect.h"
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
	Item(ItemID id, const std::string& n, ItemType t, const StatsData& sd, float p, float w, ItemEffect ie, int pow, AttackPower ap, float rm, ArmorType at);

	void setQuantity(int x) { quantity = x; }
	const int getQuantity() const { return quantity; }
	ItemID getID() const { return id; }
	const std::string& getName() const { return name; }
	ItemType getType() const { return type; }
	ArmorType getArmorType() const { return armorType; }
	const StatsData& getStats() const { return bonusStats; }
	float getPrice() const { return price; }
	float getWeight() const { return weight; }
	const ItemEffect getItemEffect() const { return itemEffect; }
	int getItemPower() const { return itemPower; }
	float getRangeMult() const { return rangeMultiplier; }
	AttackPower getAttackPower() const { return attackPower; }

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
	ItemEffect itemEffect;
	int itemPower;
	AttackPower attackPower;
	float rangeMultiplier = 1.f;
	ArmorType armorType;
	//Effect effect;
	//StateEffect se;

};