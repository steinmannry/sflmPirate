#pragma once
#include "statsData.h"
#include "statsMode.h"

//element enum?


struct Stats {
	Stats() = default;
	Stats(StatsMode m);
	Stats(const StatsData& d);
	void rollStats();
	void adjustStats();

	StatsMode statsMode;

	int maxHP = 10;
	int maxMP = 3;
	float STR = 1.f;
	float INT = 1.f;
	float DEX = 1.f;
	float CON = 1.f;
	float CHA = 1.f;	
	float LUK = 1.f;
	float DEF = 1.f;
	float SPD = 1.f;
};