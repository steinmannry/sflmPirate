#include "actor.h"
#include "animation.h"
#include "animationLibrary.h"
#include "textureManager.h"
#include <iostream>

Actor::Actor(AnimationLibrary& lib, const sf::Texture& tex) 
	: PlayerPawn() {
	sprite.setTexture(tex);
	buildAnimation(tex, lib);
	sprite.setOrigin(anim.getFrameRect().width / 2.f, anim.getFrameRect().height / 2.f);
}

void Actor::update(float dt) {
	handleInput();

	sf::Vector2f pos = sprite.getPosition();
	pos += direction * speed * dt;
	anim.update(dt);

	updateAnimDirection();
	sprite.setPosition(pos);	
	boundsCheck();	
}

void Actor::draw(sf::RenderWindow& window) {
	window.draw(sprite);
}
 

void Actor::handleInput() {
	if (sf::Joystick::isConnected(0)) {
		/*float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
		float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
		if (x)*/
		float px = sf::Joystick::getAxisPosition(0, sf::Joystick::PovX);
		float py = sf::Joystick::getAxisPosition(0, sf::Joystick::PovY);

		sf::Vector2f dir(0.f, 0.f);

		if (px < -50)  dir.x = -1.f;   // left
		if (px > 50)  dir.x = 1.f;   // right
		if (py < -50)  dir.y = 1.f;   // up
		if (py > 50)  dir.y = -1.f;   // down
		direction = dir;

		if (sf::Joystick::isButtonPressed(0, 0)) {
			//do stuff
		}
	}
}

sf::Vector2f Actor::getPos() const {
	return sprite.getPosition();
}

void Actor::updateAnimDirection() {
	const sf::IntRect& rect = anim.getFrameRect();

	sprite.setTextureRect(anim.getFrameRect());
	sprite.setOrigin(rect.width / 2.f, rect.height / 2.f);

	if (direction.x == 1) {
		sprite.setScale(1.f, 1.f);
		anim.play("walkRL");
	}
	if (direction.x == -1) {
		sprite.setScale(-1.f, 1.f);
		anim.play("walkRL");
	}
}

void Actor::loadAnimation(const std::string& key, AnimationLibrary& lib, const sf::Texture& tex) {
	const AnimationData& data = lib.get(key);

	Animation animObj(
		&tex,
		data.frameWidth,
		data.frameHeight,
		data.frameCount,
		data.frameTime,
		data.row,
		data.loop,
		data.reverse
	);
	anim.addAnimation(key, animObj);
}

void Actor::buildAnimation(const sf::Texture& tex, AnimationLibrary& lib) {
	loadAnimation("walkRL", lib, tex);
	//loadAnimation("walkUp", lib, tex);
	//loadAnimation("walkDown", lib, tex);
	//loadAnimation("IdleRL", lib, tex);

	anim.play("walkRL"); //set play to idle when anim available
	sprite.setTextureRect(anim.getFrameRect());
}

void Actor::setWorldBounds(Area& a) {
	worldBounds = a;
}

sf::FloatRect Actor::pawnBounds() {
	return sprite.getGlobalBounds();
}

void Actor::boundsCheck() {
	sf::Vector2f pos = sprite.getPosition();
	auto rect = sprite.getTextureRect();
	float spriteSizeX = rect.width / 2;
	float spriteSizeY = rect.height / 2;

	pos.x = std::clamp(pos.x, worldBounds.topLeft.x + spriteSizeX, worldBounds.bottomRight.x - spriteSizeX);
	pos.y = std::clamp(pos.y, worldBounds.topLeft.y + spriteSizeY, worldBounds.bottomRight.y - spriteSizeY);

	sprite.setPosition(pos);
}