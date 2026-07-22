#include "enemyBattleController.h"
#include "actor.h"

EnemyBattleController::EnemyBattleController(Actor* a, std::vector<Actor*>& all) : actor(a), allActors(all) {
	attackRange = a->getAttackRange();
	maxMove = actor->getMovementRange() * actor->getMovementRange();
}

void EnemyBattleController::update(float dt) {
	std::vector<Actor*> inRange = getActorsInRange();
	Actor* target = findNearest();

	if (!hasMoved) {
		startPos = actor->getPos();
		hasMoved = true;
	}
	

	if (inRange.size() == 1 && !hasActed) {
		inRange[0]->takeDamage(actor->attack());
		hasActed = true;
	}//has acted, may still move

	if (inRange.size() > 1) {
		if (!hasActed) {
			target = findWeakest();
			target->takeDamage(actor->attack());
			hasActed = true;
		}		
	}//has acted, may still move

	
	if (calcDistance(actor->getPos(), startPos) < maxMove) {
		moveTowards(target->getPos(), dt);
	}

	if (calcDistance(actor->getPos(), startPos) >= maxMove && inRange.empty()) {
		turnOver = true;
		return;
	}
}




Actor* EnemyBattleController::findNearest() {
	Actor* best = nullptr;
	float bestDist = (actor->getWorldBounds().x + actor->getWorldBounds().y);

	for (auto& a : allActors) {
		if (a->getOwner() == Owner::Enemy)
			continue;
		if (a->getState() == ActorState::Hidden) {
			continue;
		}

		float dist = calcDistance(a->getPos(), actor->getPos());

		if (dist < bestDist) {
			bestDist = dist;
			best = a;
		}
	}
	return best;
}


float EnemyBattleController::calcDistance(sf::Vector2f to, sf::Vector2f from) {
	float dx = to.x - from.x;
	float dy = to.y - from.y;
	float dist = dx * dx + dy * dy;
	return dist;
}


Actor* EnemyBattleController::findWeakest() {
	Actor* best = nullptr;
	int lowestHP = 500;

	for (auto& a : allActors) {
		if (a->getOwner() == Owner::Enemy)
			continue;

		if (a->getHP() < lowestHP) {
			lowestHP = a->getHP();
			best = a;
		}
	}
	return best;
	
}

void EnemyBattleController::moveTowards(sf::Vector2f targetPos, float dt) {
	sf::Vector2f pos = actor->getPos();
	sf::Vector2f dir = targetPos - pos;

	float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
	if (len == 0) {
		hasMoved = true;
		return;
	}

	float maxMove = actor->getMovementRange();

	
	dir.x /= len;
	dir.y /= len;
	//desiredDir = dir;
	actor->setDirection(dir);
	actor->update(dt);

	/*
	if (!actor->isBlockedX() && !actor->isBlockedY()) {
		lastGoodDir = desiredDir;
		actor->setDirection(desiredDir);
	}

	if (actor->isBlockedX()) {
		sf::Vector2f slide = sf::Vector2f(desiredDir.y, 0.f);
		actor->setDirection(slide);
	}

	if (actor->isBlockedY()) {
		sf::Vector2f slide = sf::Vector2f(0.f, desiredDir.x);
		actor->setDirection(slide);
	}



	
	sf::Vector2f avoid = avoidCollision();
	//dir = targetPos - pos + avoid * .5f;

	float finalLen = std::sqrt(dir.x * dir.x + dir.y * dir.y);
	if (finalLen > 0) {
		dir.x /= finalLen;
		dir.y /= finalLen;
	}
	*/

	
}

//sf::Vector2f EnemyBattleController::avoidCollision() {
	//sf::Vector2f avoid(0.f, 0.f);



	//float dist = calcDistance(a, actor);

	/*if (dist < 50.f) { // collision radius
		sf::Vector2f push = actor->getPos() - a->getPos();
		float len = std::sqrt(push.x * push.x + push.y * push.y);
		if (len > 0) {
			push.x /= len;
			push.y /= len;
			avoid += push;*/
//}


std::vector<Actor*> EnemyBattleController::getActorsInRange() {
	std::vector<Actor*> actorsInRange;
	for (auto& a : allActors) {
		if (a->getOwner() == Owner::Enemy)
			continue;
		if (a->getState() == ActorState::Hidden)
			continue;

		if (calcDistance(a->getPos(), actor->getPos()) <= actor->getAttackRange())
			actorsInRange.push_back(a);
	}
	return actorsInRange;
}
