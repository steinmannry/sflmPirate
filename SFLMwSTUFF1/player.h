#pragma once
#include "playerPawn.h"
#include <vector>

class Boat;
class Actor;
class Scene;


class Player {
public:
	Player();
	void handleInput();

	void setScene(Scene* s);
	void setActivePawn(PlayerPawn* p);
	PlayerPawn* getActivePawn() { return activePawn; }

	void addPawn(PlayerPawn* p);

	void update(float dt);	
	sf::Vector2f getCamPos();
	sf::Vector2f getPawnPos();

private:
	Scene* scene;
	PlayerPawn* activePawn;
	std::vector<Boat*> playerBoats;
	std::vector<Actor*> crew;
	std::vector<PlayerPawn*> playerPawns; // boats and actors

	sf::Vector2f cameraPos;
};