#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "textureManager.h"
#include "animationLibrary.h"
#include "gameState.h"
#include "player.h"
#include "menu.h"
//#include "scene.h"


class Scene;
class Boat;
class Actor;

class Engine {
public:
	Engine();
	~Engine();
	GameState state = GameState::Game;
	void run();
	void update(float dt);
	void draw();
	
	void init();
	const AnimationData& getAnimationData(const std::string& name) const;
	void loadTextures();
	void loadScene(const std::string& path);

	sf::RenderWindow& getWindow() { return window; }

private:
	TextureManager textures;
	AnimationLibrary animationLibrary;
	
	Player player;
	std::unique_ptr<Scene> scene;
	std::vector<std::unique_ptr<Boat>> allBoats;

	std::unique_ptr<Menu> menu;
	sf::RenderWindow window;
};