#pragma once
#include <SFML/Graphics.hpp>
#include "pawn.h"
#include "animationController.h"
#include "enemyBattleController.h"
#include "actorData.h"
#include "level.h"
#include "stats.h"
#include "equipment.h"
#include "inventory.h"	
#include "actorState.h"

class AnimationLibrary;
class TextureManager;
class EnemyBattleController;

class Actor : public Pawn {
public:
	Actor(const ActorData& d, AnimationLibrary& lib, const sf::Texture& tex);

	void update(float dt) override;
	void draw(sf::RenderWindow& window) override;
	void handleInput() override;

	void setScene(Scene* s) override { scene = s; }
	//--------------ENEMY_AI------------------
	void setController(EnemyBattleController* c) { aiController = c; }
	EnemyBattleController* getController() { return aiController; }
	bool isBlockedX() const { return blockedX; }
	bool isBlockedY() const { return blockedY; }

	//----------------GRAPHICS----------------//
	sf::Vector2f getPos() const override { return sprite.getPosition(); }
	void setPos(sf::Vector2f pos) override { sprite.setPosition(pos); }
	void setWorldBounds(Area& a) override { worldBounds = a; }
	sf::FloatRect pawnBounds() override;
	sf::FloatRect getGlobalBounds() override { return sprite.getGlobalBounds(); }
	void updateAnimDirection();
	AnimationController& getAnimController() { return anim; }
	const AnimationController& getAnimController() const { return anim; }
	void boundsCheck();
	sf::Sprite& getSprite() override { return sprite; } 
	sf::Vector2f getWorldBounds() { return worldBounds.size(); }
	void setDirection(sf::Vector2f dir) { direction = dir; }
	

	//----------------STATS----------------//
	std::string& getName() { return name; }
	void applyEquipBonus();
	int getHP() const { return currentHP; }
	int getMP() const { return currentMP; }
	void setHP(int x) { currentHP += x; }
	void setMP(int x) { currentMP += x; }
	Stats getAdjustedStats() const { return adjustedStats; }
	ActorState getState() const { return actorState; }

	//-------------BATTLE------------------//
	void disableInput() { disable = true; }
	void enableInput() { disable = false; }
	float getMovementRange() { return movementRange; }
	float getAttackRange() { return attackRange;  }
	void setAttackRange(float x) { attackRange += x; }

	float attack();
	int takeDamage(int x);
	bool dodge_crit() const;

	//----------------INVENTORY----------------//
	Inventory& getInventory() { return inventory; }
	const Inventory& getInventory() const { return inventory; }
	float getWeightCapacity() const { return weightCapacity; }
	Equipment& getEquipment() { return equipment; }	


private:
	Owner owner;
	ActorData data;
	Stats baseStats;
	Stats adjustedStats;
	AnimationController anim;
	sf::Sprite sprite;
	sf::FloatRect collisionBounds;
	Area worldBounds;
	sf::Vector2f direction{ 0, 0 };

	std::string name;
	std::string className;
	LevelData levelData;
	ActorState actorState = ActorState::None;
	
	Inventory inventory;
	Equipment equipment;
	float weightCapacity = 20.f;
	float gold = 25;
	float speed = 30.f;
	Scene* scene = nullptr;

	float timer = 0.f;
	//---------Battle-Crap---------//
	int currentHP = 1;
	int currentMP = 1;
	float movementRange = 30.f;
	float attackRange = 42.f;
	float baseAttackRange = 42.f;

	bool disable = false;
	EnemyBattleController* aiController = nullptr;
	bool blockedX = false;
	bool blockedY = false;
};