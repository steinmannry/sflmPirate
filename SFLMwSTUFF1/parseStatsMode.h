#pragma once
#include "statsMode.h"
#include "owner.h"
#include <string>

inline StatsMode parseStatsMode(const std::string& s) {
	if (s == "Random") return StatsMode::Random;
	return StatsMode::Custom;
}

inline Owner parseOwner(const std::string& s) {
	if (s == "Player") return Owner::Player;
	if (s == "Enemy") return Owner::Enemy;
}