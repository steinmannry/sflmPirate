#pragma once
#include <SFML/Graphics.hpp>
#include "playerPawn.h"
#include "animationController.h"


class AnimationLibrary;
class TextureManager;


class Actor : public PlayerPawn {
public:
	Actor(AnimationLibrary& lib, const sf::Texture& tex);
	void update(float dt) override;
	void draw(sf::RenderWindow& window) override;
	sf::Vector2f getPos() const override;
	void setWorldBounds(Area& a) override;
	void handleInput() override;
	sf::FloatRect pawnBounds() override;

	void updateAnimDirection();
	void loadAnimation(const std::string& key, AnimationLibrary& lib, const sf::Texture& tex);
	void buildAnimation(const sf::Texture& t, AnimationLibrary& lib);
	void boundsCheck();
private:
	AnimationController anim;
	sf::Sprite sprite;
	Area worldBounds;
	sf::Vector2f direction{ 0, 0 };
	float speed = 160.f;


};