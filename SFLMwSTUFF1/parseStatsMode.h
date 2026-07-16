#pragma once
#include "statsMode.h"
#include <string>

inline StatsMode parseStatsMode(const std::string& s) {
	if (s == "Random") return StatsMode::Random;
	return StatsMode::Custom;
}