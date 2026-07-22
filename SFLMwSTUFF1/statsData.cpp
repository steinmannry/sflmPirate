#include "statsData.h"

StatsData& StatsData::operator+=(const StatsData& other) {
	maxHP += other.maxHP;
	maxMP += other.maxMP;
	STR += other.STR;
	INT += other.INT;
	DEX += other.DEX;
	CON += other.CON;
	CHA += other.CHA;
	LUK += other.LUK;
	DEF += other.DEF;
	SPD += other.SPD;
	return *this;
}

StatsData& StatsData::operator-=(const StatsData& other) {
	maxHP -= other.maxHP;
	maxMP -= other.maxMP;
	STR -= other.STR;
	INT -= other.INT;
	DEX -= other.DEX;
	CON -= other.CON;
	CHA -= other.CHA;
	LUK -= other.LUK;
	DEF -= other.DEF;
	SPD -= other.SPD;
	return *this;
}