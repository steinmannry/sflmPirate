#pragma once
#include <SFML/Graphics.hpp>
#include "playerPawn.h"
#include "animationController.h"
#include "actorData.h"
#include "level.h"
#include "stats.h"
#include "equipment.h"
#include "inventory.h"	

class AnimationLibrary;
class TextureManager;


class Actor : public PlayerPawn {
public:
	Actor(const ActorData& d, AnimationLibrary& lib, const sf::Texture& tex);
	void update(float dt) override;
	void draw(sf::RenderWindow& window) override;
	void handleInput() override;

	void setScene(Scene* s) override { scene = s; }

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
	
	

	//----------------STATS----------------//
	std::string& getName() { return name; }


	//----------------INVENTORY----------------//
	Inventory& getInventory() { return inventory; }
	const Inventory& getInventory() const { return inventory; }
	float getWeightCapacity() const { return weightCapacity; }
	Equipment& getEquipment() { return equipment; }	


private:
	ActorData data;
	AnimationController anim;
	sf::Sprite sprite;
	sf::FloatRect collisionBounds;
	Area worldBounds;
	sf::Vector2f direction{ 0, 0 };

	std::string name;
	std::string className;
	LevelData levelData;
	Stats stats;
	Equipment equipment;
	Inventory inventory;
	float weightCapacity = 20.f;
	Scene* scene = nullptr;


};