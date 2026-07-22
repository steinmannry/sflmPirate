#include "battleScene.h"
#include "actor.h"
#include <iostream>

BattleScene::BattleScene(TextureManager& texture, AnimationLibrary& al, const SceneData& sd)
	: Scene(texture, al, sd) {
		
	movementRangeDisplay.setFillColor(sf::Color(0, 0, 100, 50));
	attackRangeDisplay.setFillColor(sf::Color(100, 0,0,50));
}

//void BattleScene::update(float dt, Pawn* p) {
//updateCamera(dt, p->getPos());
//updateMovement(dt, p);
//checkBlockingCollision(p);



void BattleScene::draw(sf::RenderWindow& window, Pawn* p) {
	window.setView(camera);
	if (skyGrad)
		window.draw(skyGradient);
	if (groundGrad)
		window.draw(groundGradient);
	if (map)
		map->draw(window);
	if (p) {
		p->draw(window);
	}

	if (battleState == BattleState::Attack) {

	}
	
	if (battleState == BattleState::Placement) {
		for (auto& a : allCombatants) {
			if (a->getOwner() == Owner::Enemy)
				a->draw(window);
		}
	}

	if (battleState != BattleState::Placement) {
		for (auto& a : allCombatants) {
			a->draw(window);

			if (a == currentActor && a->getOwner() == Owner::Player) {
				if (battleState == BattleState::Init || battleState == BattleState::Movement) {
					window.draw(movementRangeDisplay);
					battleWindow.draw(window);
				}
				if (battleState == BattleState::Attack) {
					window.draw(attackRangeDisplay);
					buildTargetDisplay();
					window.draw(targetDisplay);
					//battleWindow.draw(window);
				}
			}
		}
	}
}




void BattleScene::updateMovement(float dt, Pawn* p) {
	for (auto& a : allCombatants) {
		a->update(dt);
		checkBlockingCollision(a);
	}

	//switch (battleState)


	if (battleState == BattleState::Placement) {
		updatePlacement(allCombatants[placementIndex], dt);
	}

	//-----------INITIALIZE BATTLE---------------
	if (battleState == BattleState::Init) {
		if (!currentActor) {//set nullptr after turn 
		getNextActor();
	}
	


	//--------------------ENEMY_TURN---------------------
		if (currentActor->getOwner() == Owner::Enemy) {
			if (currentActor->getController()->isTurnOver()) {
				currentActor->getController()->resetTurnOver();
				getNextActor();
				return;
			}
			currentActor->getController()->update(dt);
		}


		//--------------PLAYER_TURN--------------------------
		if (currentActor->getOwner() == Owner::Player) {
			buildMovementRange(currentActor);
			battleWindow.buildNameBox(currentActor->getName());
			battleState = BattleState::CommandWindow;
		}
	}
	
	//----------------COMMAND_WINDOW------------------------
	if (battleState == BattleState::CommandWindow) {
		battleWindow.update(dt);

		if (battleWindow.getCommand() == Command::Move) {

			startPos = currentActor->getPos();
			currentActor->update(dt);

			sf::Vector2f newPos = currentActor->getPos();

			float dx = newPos.x - movementStartPos.x;
			float dy = newPos.y - movementStartPos.y;

			float maxMove = currentActor->getMovementRange();

			if (dx * dx + dy * dy > maxMove * maxMove) {
				currentActor->setPos(movementStartPos);
			}

			if (sf::Joystick::isButtonPressed(0, 0)) {
				battleState = BattleState::CommandWindow;
				return;
			}
		}	

		if (battleWindow.getCommand() == Command::Attack) {
			battleState == BattleState::Attack;
			if (sf::Joystick::getAxisPosition(0, sf::Joystick::PovX) > 50) {
				targetIndex = targetIndex + 1;
				if (targetIndex >= targetsInRange.size())
					targetIndex = 0;
			}
			if (sf::Joystick::getAxisPosition(0, sf::Joystick::PovX) < -50) {
				targetIndex = targetIndex - 1;
				if (targetIndex < 0)
					targetIndex = targetsInRange.size() -1;
			}

			//-------ATTACK--------
			if (sf::Joystick::isButtonPressed(0, 0)) {
				Actor* target = targetsInRange[targetIndex];
				int dmg = target->takeDamage(currentActor->attack());
				std::cout << target->getName() << " took " << dmg << " damage\n";

			}

		}
	}
	
}

void BattleScene::getNextActor() {
	if (!readyActors.empty()){
		currentActor = readyActors.front();
		readyActors.erase(readyActors.begin());
		return;
	}

	while (readyActors.empty()) {
		readyActors = tom.tick();
		currentActor = readyActors.front();
		readyActors.erase(readyActors.begin());
	}		
}

void BattleScene::buildMovementRange(Actor* a) {
	float range = a->getMovementRange();
	movementRangeDisplay.setRadius(range);

}

void BattleScene::buildAttackRange(Actor* a) {
	float range = a->getAttackRange();
	attackRangeDisplay.setRadius(range);
}


bool BattleScene::isInRange(sf::Vector2f from, sf::Vector2f to, float radius) {
	float dx = from.x - to.x;
	float dy = from.y - to.y;

	if (dx * dx + dy * dy <= radius * radius) {
		return true;
	}
	return false;
}

void BattleScene::selectTargets() {
	targetsInRange.clear();
	for (auto& a : allCombatants) {
		if (isInRange(currentActor->getPos(), a->getPos(), currentActor->getAttackRange())) {
			targetsInRange.push_back(a);
		}
	}
	targetIndex = 0;
}

void BattleScene::buildTargetDisplay() {
	if (!targetsInRange.empty()) {
		Actor* t = targetsInRange[targetIndex];

		targetDisplay.setRadius(32.f);
		targetDisplay.setPosition(t->getPos());

		if (t->getOwner() == Owner::Enemy) {
			targetDisplay.setFillColor(sf::Color(100, 0, 0, 125));
		}
		if (t->getOwner() == Owner::Player) {
			targetDisplay.setFillColor(sf::Color(0, 0, 100, 125));
		}
		
	}
	
}

void BattleScene::updatePlacement(Actor* a, float dt) {
	if (a->getOwner() != Owner::Player) {
		placementIndex++;
		return;
	}
	
	sf::Vector2f pos = startPos;
	a->enableInput();
	float placementRadius = a->getMovementRange();
	// Direct movement input (no acceleration, no physics)
	/*
	if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 20)
		pos.x += 100 * dt;
	if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -20)
		pos.x -= 100 * dt;
	if (sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > 20)
		pos.y += 100 * dt;
	if (sf::Joystick::getAxisPosition(0, sf::Joystick::Y) < -20)
		pos.y -= 100 * dt;

	// Clamp to placement radius
	float dx = pos.x - startPos.x;
	float dy = pos.y - startPos.y;

	if (dx * dx + dy * dy <= placementRadius * placementRadius) {
		a->setPos(pos);
	}
	*/
	
	if (calcDistance(a->getPos(), startPos) < placementRadius * placementRadius)
		placementPos = a->getPos();

	if (calcDistance(a->getPos(), startPos) >= placementRadius * placementRadius)
		//a->setPos(placementPos);
	

	if (sf::Joystick::isButtonPressed(0, 0)) {
		placementIndex++;


		if (placementIndex >= allCombatants.size()) {
			battleState = BattleState::Init;
		}
	}
}

float BattleScene::calcDistance(sf::Vector2f to, sf::Vector2f from) {
	float dx = to.x - from.x;
	float dy = to.y - from.y;
	float dist = dx * dx + dy * dy;
	return dist;
}

void BattleScene::onBattleEnter(std::vector<Actor*> crew, sf::Vector2f pos, std::vector<Actor*> enemies) {
	for (auto& c : crew) {
		c->disableInput();
		allCombatants.push_back(c);
	}
	for (auto& e : enemies) {
		e->setController(new EnemyBattleController(e, allCombatants));
		allCombatants.push_back(e);
		
	}
	startPos = pos;
	tom.init(allCombatants);
	readyActors.clear();
	battleState = BattleState::Placement;
}