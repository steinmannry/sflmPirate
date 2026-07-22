#pragma once
#include <SFML/Graphics.hpp>
#include "animationController.h"
#include "area.h"
#include "owner.h"

class Scene;



class Pawn{
public:
	Pawn() = default;
	virtual ~Pawn() = default;	
	
	virtual void update(float dt) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual sf::Vector2f getPos() const = 0;
	virtual void setPos(sf::Vector2f pos) = 0;
	virtual void handleInput() = 0;//float dt in parameter???
	virtual void setWorldBounds(Area& a) = 0;
	virtual sf::FloatRect pawnBounds() = 0;
	virtual sf::FloatRect getGlobalBounds() = 0;
	virtual void setScene(Scene* s) = 0;
	void setOwner(Owner o) { owner = o; }
	virtual sf::Sprite& getSprite() = 0;
	Owner getOwner() const { return owner; }
protected:
	Scene* scene = nullptr;
	Owner owner = Owner::Player;
};