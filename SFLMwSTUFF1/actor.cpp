#include "actor.h"
#include "scene.h"
#include "animation.h"
#include "animationLibrary.h"
#include "textureManager.h"
#include <iostream>

Actor::Actor(const ActorData& d, AnimationLibrary& lib, const sf::Texture& tex)
	: PlayerPawn(), data(d),
	stats(data.statsMode == StatsMode::Random ? Stats(StatsMode::Random) : Stats(d.stats)){

	name = data.name;
	className = data.className;
	levelData.level = data.level;
	levelData.statPoints = static_cast<float>(levelData.level * .5);
	inventory.setOwner(this);
	equipment.setOwner(this);
	weightCapacity += data.stats.CON + data.stats.STR;

	sprite.setTexture(tex);
	//pawnBounds();
}

void Actor::update(float dt) {
	handleInput();
	//sprite.move(direction * stats.SPD * dt);
	
	sf::Vector2f pos = sprite.getPosition();
	sf::Vector2f oldPos = pos;
		
	pos.x += direction.x * stats.SPD * dt;
	sprite.setPosition(pos);
	if (scene->checkCollision(this)) {
		pos.x = oldPos.x;
		sprite.setPosition(pos);
	}

	pos.y += direction.y * stats.SPD * dt;
	sprite.setPosition(pos);
	if (scene->checkCollision(this)) {
		pos.y = oldPos.y;
		sprite.setPosition(pos);
	}

	anim.update(dt);
	updateAnimDirection();	
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
			std::cout << sprite.getPosition().x << " " << sprite.getPosition().y << "\n";
		}
	}
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



void Actor::boundsCheck() {
	sf::Vector2f pos = sprite.getPosition();
	auto rect = sprite.getTextureRect();
	float spriteSizeX = rect.width / 2;
	float spriteSizeY = rect.height / 2;

	pos.x = std::clamp(pos.x, worldBounds.topLeft.x + spriteSizeX, worldBounds.bottomRight.x - spriteSizeX);
	pos.y = std::clamp(pos.y, worldBounds.topLeft.y + spriteSizeY, worldBounds.bottomRight.y - spriteSizeY);

	sprite.setPosition(pos);
}


sf::FloatRect Actor::pawnBounds() {
	collisionBounds = sprite.getGlobalBounds();
	collisionBounds.top += 32;
	collisionBounds.height -= 32;
	return collisionBounds;
}

