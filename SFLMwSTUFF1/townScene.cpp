#include "townScene.h"
#include <iostream>

void TownScene::updateMovement(float dt, Pawn* p) {
	checkTriggerCollision(p);
}


void TownScene::checkTriggerCollision(Pawn* p) {
	if (!map) return;
	sf::FloatRect pawnBounds = p->pawnBounds();

	const auto& sprites = map->getObjSprites();
	const auto& instances = map->getObjectInstances();
	const auto& types = map->getObjectData();

	for (size_t i = 0; i < sprites.size(); ++i) {
		const auto& inst = instances[i];
		const auto& type = types.at(inst.type);
		const auto& sprite = sprites[i];

		if (pawnBounds.intersects(sprite.getGlobalBounds()) && type.trigger == TriggerType::Proximity) {
			if (type.eventType == EventType::SceneChange) {
				if (!type.targetScene.empty())
					pendingScene = type.targetScene;
				//requestSceneChange(type.targetScene);				
			}
		}
	}
}