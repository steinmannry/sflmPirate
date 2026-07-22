#include "actor.h"
#include "scene.h"
#include "animation.h"
#include "animationLibrary.h"
#include "textureManager.h"
#include "random.h"
#include <iostream>
#include <cmath>

Actor::Actor( const ActorData& d, AnimationLibrary& lib, const sf::Texture& tex)
	: Pawn(), owner(d.owner), data(d),
	baseStats(data.statsMode == StatsMode::Random ? Stats(StatsMode::Random) : Stats(d.stats)){
	adjustedStats = baseStats;
	sprite.setTexture(tex);
	name = data.name;
	className = data.className;
	levelData.level = data.level;
	levelData.statPoints = static_cast<float>(levelData.level * .5);
	inventory.setOwner(this);
	equipment.setOwner(this);
	weightCapacity += data.stats.CON + data.stats.STR;
	gold += baseStats.CHA * baseStats.LUK;
	speed += baseStats.SPD;
	
	currentHP = adjustedStats.maxHP;
	currentMP = adjustedStats.maxMP;
	movementRange += adjustedStats.SPD + (adjustedStats.CON * 4.f );
	
	//adjustedStats.DEF += 
	
}

void Actor::update(float dt) {
	if (!disable) {
		handleInput();
	}
	//sprite.move(direction * stats.SPD * dt);
	blockedX = false;
	blockedY = false;

	sf::Vector2f pos = sprite.getPosition();
	sf::Vector2f oldPos = pos;
		
	pos.x += direction.x * speed * dt;
	sprite.setPosition(pos);
	if (scene->checkBlockingCollision(this)) {
		pos.x = oldPos.x;
		sprite.setPosition(pos);
		blockedX = true;
	}

	pos.y += direction.y * speed * dt;
	sprite.setPosition(pos);
	if (scene->checkBlockingCollision(this)) {
		pos.y = oldPos.y;
		sprite.setPosition(pos);
		blockedY = true;
	}

	timer += dt;
	if (timer <= 1.f) {
		std::cout << "dirX: " << direction.x << " dirY: " << direction.y << "\n";
		timer = 0;
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

		if (px < -50)  dir.x = -1.f;  // left
		if (px > 50)  dir.x = 1.f;   // right
		if (py < -50)  dir.y = 1.f;   // up
		if (py > 50)  dir.y = -1.f;   // down
		direction = dir;

		if (sf::Joystick::isButtonPressed(0, 0)) {
			std::cout << sprite.getPosition().x << " " << sprite.getPosition().y << "\n";
		}
	}
}


//---------------BATTLE-------------------------//

float Actor::attack() {
	AttackPower ap = getEquipment().getWeapon()->getAttackPower();
	float atk = Random::get(ap.minDamage, ap.maxDamage);
	if (dodge_crit()) {
		atk *= 1.5;
	}
	return atk + adjustedStats.STR;
}

int Actor::takeDamage(int x) {
	if (dodge_crit()) {
		return 0;
	}
	float dmg = x * adjustedStats.DEF;
	currentHP -= static_cast<int>(std::round(dmg));

	return dmg;
}

bool Actor::dodge_crit() const{
	int dodge = static_cast<int>(std::round(adjustedStats.DEX));
	int chance = Random::get(1, 100);

	if (chance <= dodge)
		return true;
	return false;
}



//----------------MOVEMENT--------------------------//

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
	auto& rect = sprite.getTextureRect();
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

//------------STATS-----------------

void Actor::applyEquipBonus() {
	StatsData bonus = getEquipment().getTotalBonus();

	adjustedStats = baseStats;

	adjustedStats.maxHP += bonus.maxHP;
	adjustedStats.maxMP += bonus.maxMP;
	adjustedStats.STR += bonus.STR;
	adjustedStats.INT += bonus.INT;
	adjustedStats.DEX += bonus.DEX;
	adjustedStats.CON += bonus.CON;
	adjustedStats.CHA += bonus.CHA;
	adjustedStats.LUK += bonus.LUK;
	adjustedStats.DEF += bonus.DEF;
	adjustedStats.SPD += bonus.SPD;

	adjustedStats.adjustStats();

	attackRange = baseAttackRange * (getEquipment().getWeapon() ? getEquipment().getWeapon()->getRangeMult() : 1.f);
}