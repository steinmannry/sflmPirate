#pragma once
#include <SFML/Graphics.hpp>

class Actor;

class EnemyBattleController {
public:
	EnemyBattleController(Actor* a, std::vector<Actor*>& all);
	void update(float dt);
	
	std::vector<Actor*> getActorsInRange();

	Actor* findNearest();
	Actor* findWeakest();
	
	//Actor* findLeader();
	//heal, attack healer, gaurd target, avoid threat
	//sf::Vector2f avoidCollision();

	void moveTowards(sf::Vector2f targetPos, float dt);
	float calcDistance(sf::Vector2f to, sf::Vector2f from);
	bool isTurnOver() { return turnOver; }
	void resetTurnOver() { turnOver = false; }
private:
	Actor* actor;
	std::vector<Actor*>& allActors;
	//std::vector<Actor*>& actorsInRange{};

	Actor* target = nullptr;
	
	float attackRange;
	float maxMove;
	sf::Vector2f startPos;
	sf::Vector2f desiredDir;
	sf::Vector2f lastGoodDir;
	bool hasActed = false;
	bool hasMoved = false;
	bool turnOver = false;
};