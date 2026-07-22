#pragma once
#include "scene.h"


class TownScene : public Scene {
public: 
	using Scene::Scene;
protected:
	void updateMovement(float dt, Pawn* p) override;

private:
	void checkTriggerCollision(Pawn* p);
};

