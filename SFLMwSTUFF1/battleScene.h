#pragma once
#include "scene.h"
#include "turnOrderManager.h"
#include "battleWindow.h"

class Actor;

enum class BattleState{Placement, Init, CommandWindow, Movement, Attack};

class BattleScene : public Scene {
public:
	BattleScene(TextureManager& texture, AnimationLibrary& al, const SceneData& sd);
	
	void onBattleEnter(std::vector<Actor*> crew, sf::Vector2f pos, std::vector<Actor*> enemies) override;
	
	//void update(float dt, Pawn* p) override;
	void draw(sf::RenderWindow& window, Pawn* p) override;
protected:
	void updateMovement(float dt, Pawn* p) override;

private:
	void getNextActor();
	bool isInRange(sf::Vector2f from, sf::Vector2f to, float radius);
	void buildMovementRange(Actor* a);
	void buildAttackRange(Actor* a);
	void buildTargetDisplay();
	void selectTargets();

	void updatePlacement(Actor* a, float dt);
	float calcDistance(sf::Vector2f to, sf::Vector2f from);

	std::vector<Actor*> allCombatants;
	std::vector<Actor*> readyActors;
	std::vector<Actor*> targetsInRange;
	int targetIndex = 0;
	TurnOrderManager tom;
	Actor* currentActor = nullptr;
	float partyPlacementRange = 150.f;

	sf::Vector2f startPos;
	sf::Vector2f placementPos;
	sf::Vector2f movementStartPos;
	int placementIndex = 0;

	BattleWindow battleWindow;
	sf::CircleShape movementRangeDisplay;
	sf::CircleShape attackRangeDisplay;	
	sf::CircleShape targetDisplay;
	bool movement = false;
	bool battleOver = false;
	BattleState battleState = BattleState::Init;
};