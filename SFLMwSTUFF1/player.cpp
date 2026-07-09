#include "player.h"
#include <SFML/Graphics.hpp>
#include "boat.h"
#include "actor.h"
#include "scene.h"

Player::Player() : scene(nullptr), activePawn(nullptr){
}

void Player::update(float dt) {
	cameraPos = activePawn->getPos();
	handleInput();
	
	if (activePawn) {
		activePawn->handleInput();
		activePawn->update(dt);
	}
}

void Player::handleInput() {
	//menu ui input
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