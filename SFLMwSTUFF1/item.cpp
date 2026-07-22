#include "item.h"

Item::Item(ItemID id, const std::string& n, ItemType t, 
	const StatsData& sd, float p, float w, const ItemEffect ie, int pow, AttackPower ap, float rm,  ArmorType at)
		: id(id), name(n), type(t), bonusStats(sd), price(p), weight(w), itemEffect(ie), itemPower(pow), attackPower(ap), rangeMultiplier(rm), armorType(at){

}

