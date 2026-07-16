#include "stats.h"
#include "random.h"


Stats::Stats(StatsMode m) :statsMode(m) {
	if (statsMode == StatsMode::Random)
		rollStats();
	adjustStats();
}

Stats::Stats(const StatsData& d) :statsMode(StatsMode::Custom) {
	maxHP = d.maxHP;
	maxMP = d.maxMP;
	STR = d.STR;
	INT = d.INT;
	DEX = d.DEX;
	CON = d.CON;
	CHA = d.CHA;
	LUK = d.LUK;
	SPD = d.SPD;
	adjustStats();
}

void Stats::rollStats() {
	maxHP = Random::get(10, 25);
	maxMP = Random::get(3, 20);

	STR = Random::get(1.0f, 8.0f);	
	INT = Random::get(1.0f, 8.0f);	
	DEX = Random::get(1.0f, 8.0f);
	CON = Random::get(1.0f, 8.0f);
	CHA = Random::get(3.0f, 12.0f);
	LUK = Random::get(1.0f, 1.5f);
	SPD = Random::get(15.f, 25.f);
}

void Stats::adjustStats() {
	maxHP += static_cast<int>(maxHP * (CON / 10.f));
	maxMP += static_cast<int>(maxMP * (INT / 10.f));
	SPD *= DEX;
}