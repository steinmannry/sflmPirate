#include "player.h"
#include <SFML/Graphics.hpp>
#include "boat.h"
#include "actor.h"
#include "scene.h"
#include <iostream>

Player::Player() : scene(nullptr), activePawn(nullptr){

}

void Player::update(float dt) {
	cameraPos = activePawn->getPos();
	handleInput();

	if (gamePaused)
		return;
	
	if (activePawn) {
		activePawn->handleInput();
		activePawn->update(dt);
	}
}

void Player::handleInput() {
	if (sf::Joystick::isConnected(0)) {
		if (sf::Joystick::isButtonPressed(0, 3)) {
			requestStateChange(GameState::Menu);
			gamePaused = true;
		}		

		if (sf::Joystick::isButtonPressed(0, 2)) {
			std::cout << " crew weapon: " << crew[0]->getEquipment().getWeapon()->getName() << "\n";


		}
	}
}

void Player::addPawn(PlayerPawn* p){
	playerPawns.push_back(p);

}

sf::Vector2f Player::getCamPos() {
	return activePawn ? activePawn->getPos() : sf::Vector2f{};
}

sf::Vector2f Player::getPawnPos() {
	return activePawn ? activePawn->getPos() : sf::Vector2f{};
}

void Player::setScene(Scene* s) { scene = s; }
void Player::setActivePawn(PlayerPawn * p) { activePawn = p; }

