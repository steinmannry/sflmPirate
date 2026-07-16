#include "item.h"

Item::Item(ItemID id, const std::string& n, ItemType t, 
	const StatsData sd, float p, float w, int pow, AttackPower ap, ArmorType at)
		: id(id), name(n), type(t), bonusStats(sd), price(p), weight(w), itemPower(pow), attackPower(ap), armorType(at){

}