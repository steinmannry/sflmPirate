#pragma once

struct StatsData {
	int maxHP = 1.f;
	int maxMP = 1.f;
	float STR = 1.f;
	float INT = 1.f;
	float DEX = 1.f;
	float CON = 1.f;
	float CHA = 1.f;
	float LUK = 1.f;
	float DEF = 0.f;
	float SPD = 15.f;

	StatsData& operator+=(const StatsData& other);
	StatsData& operator-=(const StatsData& other);

};