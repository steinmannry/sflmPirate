#pragma once
#include <functional>

enum class ItemID
{
	StoneDagger,
	IronDagger,
	SilverDagger,
	ShortBow,
	WoodenArrows,
	WoodenSword,
	IronSword,
	BastardSword,
	GnarledStaff,
	OakStaff,
	EnchantedScepter,
	Robe,
	Tunic,
	LeatherArmor,
	ChainMail,
	PlateMail,
	FullPlate,
	Herb,
	Unknown
};

namespace std {
	template <>
	struct hash<ItemID> {
		std::size_t operator()(const ItemID& id) const noexcept {
			return static_cast<std::size_t>(id);
		}
	};
}