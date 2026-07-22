#include "turnOrderManager.h"
#include "actor.h"
#include <algorithm>

void TurnOrderManager::init(const std::vector<Actor*>& combatants) {
	entries.clear();
	for (auto* a : combatants)
		entries.push_back({ a, 0.f });
}

std::vector<Actor*> TurnOrderManager::tick() {
	for (auto& e : entries)
		e.meter += e.actor->getAdjustedStats().SPD;
	
	std::vector<TurnEntry*> ready;
	for (auto& e : entries)
		if (e.meter >= THRESHOLD)
			ready.push_back(&e);

	std::sort(ready.begin(), ready.end(), [](TurnEntry* a, TurnEntry* b) {
		return a->meter > b->meter;
	});

	std::vector<Actor*> result;
	for (auto* e : ready) {
		result.push_back(e->actor);
		e->meter -= THRESHOLD;
	}
	return result;
}