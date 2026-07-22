#pragma once
#include <string>
#include "jsonLoader.h"
#include "statsData.h"
#include "statsMode.h"
#include "owner.h"

struct EquipmentData {
	std::string weapon;
	std::string armor;
	std::string head;
	std::string hands;	
	std::string feet;
	std::string misc;
};

struct InventoryEntry {
	std::string id;
	int quantity = 1;
};

struct InventoryData {
	std::vector<InventoryEntry> entries;
};

struct ActorData {
	std::string id;
	std::string name;
	std::string className;
	Owner owner;
	std::string texture;
	std::vector<std::string> animations;
	int level = 1;
	StatsMode statsMode = StatsMode::Custom;
	StatsData stats;
	EquipmentData equipment;
	InventoryData inventory;
	static ActorData fromJson(const json& j);
};


