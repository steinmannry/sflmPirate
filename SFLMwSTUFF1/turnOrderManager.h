#pragma once
#include <vector>

class Actor;

struct TurnEntry {
	Actor* actor;
	float meter = 0.f;
};


class TurnOrderManager {
public:
	//TurnOrderManager();

	void init(const std::vector<Actor*>& combatants);

	std::vector<Actor*> tick();


private:
	static constexpr float THRESHOLD = 500.f;
	std::vector<TurnEntry> entries;

};