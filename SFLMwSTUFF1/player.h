#pragma once
#include "playerPawn.h"
#include "gameState.h"
#include "menu.h"
#include <vector>
#include <functional>

class Boat;
class Actor;
class Scene;



class Player {
public:
	Player();
	void handleInput();
	
	std::function<void(GameState)> requestStateChange;

	void setScene(Scene* s);
	void setActivePawn(PlayerPawn* p);
	PlayerPawn* getActivePawn() { return activePawn; }
	std::vector<std::unique_ptr<Actor>>& getCrew() { return crew; }// need to return by reference to avoid copying. no copying unique pointers
	const std::vector<std::unique_ptr<Actor>>& getCrew() const { return crew; }

	void addPawn(PlayerPawn* p);

	void update(float dt);	
	void resumeGame() { gamePaused = false; }
	sf::Vector2f getCamPos();
	sf::Vector2f getPawnPos();

private:
	Scene* scene;
	PlayerPawn* activePawn;
	std::vector<Boat*> playerBoats;
	std::vector<std::unique_ptr<Actor>> crew;
	std::vector<PlayerPawn*> playerPawns; // boats and actors

	sf::Vector2f cameraPos;
	bool gamePaused = false;

};