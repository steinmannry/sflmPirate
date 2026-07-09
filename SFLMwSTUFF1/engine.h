#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "textureManager.h"
#include "animationLibrary.h"
#include "player.h"
//#include "scene.h"

class Scene;
class Boat;
class Actor;

class Engine {
public:
	Engine();
	~Engine();
	void run();
	void update(float dt);
	void draw();
	
	const AnimationData& getAnimationData(const std::string& name) const;
	void loadScene(const std::string& path);

	sf::RenderWindow& getWindow() { return window; }

private:
	TextureManager textures;
	AnimationLibrary animationLibrary;
	sf::RenderWindow window;
	Player player;
	std::unique_ptr<Scene> scene;
	std::vector<std::unique_ptr<Boat>> allBoats;
	std::vector<std::unique_ptr<Actor>> allActors;
};