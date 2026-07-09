#pragma once
#include <SFML/Graphics.hpp>
#include "animationController.h"
#include "area.h";



class PlayerPawn{
public:
	PlayerPawn() = default;
	virtual ~PlayerPawn() = default;

	virtual void update(float dt) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual sf::Vector2f getPos() const = 0;
	virtual void handleInput() = 0;
	virtual void setWorldBounds(Area& a) = 0;
	virtual sf::FloatRect pawnBounds() = 0;
};