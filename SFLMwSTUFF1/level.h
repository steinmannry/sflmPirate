#pragma once


struct LevelData {
	int level = 1;
	int experienceRequired = 100;
	int currentExperience = 0;
	float statPoints = 0.f;

	void LevelUp() {
		level++;
		statPoints += 1.5f; 
		experienceRequired = 100 * level;
		currentExperience = 0; 
	}
};