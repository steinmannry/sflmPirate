#pragma once
#include <SFML/Graphics.hpp>
#include "playerPawn.h"
//#include "area.h"

enum class Owner { Player, Enemy };


class Boat : public PlayerPawn {
public:
	Boat(const sf::Texture& tex, Owner o, const sf::Vector2f pos, const std::string& n);
	void update(float dt);
	void draw(sf::RenderWindow& window);
	void handleInput() override;
	sf::Vector2f getPos() const override;
	sf::FloatRect pawnBounds() override;
	const sf::Sprite& getSprite() const { return sprite; }
	//void setPos(sf::Vector2f pos) { sprite.setPosition(pos); }
	//const sf::Vector2f getPos() const { return sprite.getPosition(); }
	void setRotationSpeed(float x) { rotationSpeed = x * 1.5f; }
	void setThrottle(bool tf) { throttle = tf; }

	void setWorldBounds(Area& a) { worldBounds = a; }//help
	void setOwner(Owner o) { owner = o; }
private:

	Owner owner;
	std::string name;
	sf::Sprite sprite;	
	Area worldBounds;

	//sf::Vector2f position;
	sf::Vector2f velocity = { 0.f, 0.f };
	float rotationSpeed = 0.f;
	bool throttle = false;
	float maxSpeed = 100.f;
	float thrustPower = 10.f;
	float direction = 0.f;
	float mass = 5.f;
};