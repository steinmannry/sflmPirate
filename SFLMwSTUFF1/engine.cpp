#include "engine.h"
#include "scene.h"
#include "sceneData.h"
#include "jsonLoader.h"
#include "boat.h"
#include "actor.h"
#include <fstream>
#include <iostream>


Engine::~Engine() = default;

Engine::Engine()
	: window(sf::VideoMode(800, 600), "aaaargh!") {

	textures.load("ocean", "waves2.png");
	textures.load("boat", "boat_right.png");
	textures.load("house", "house.png");
	textures.load("wildflowers", "wildflowers.png");
	textures.load("shadowman", "shadowman.png");

	animationLibrary.load("walkRL", "walk_rl.json");	
	
	allBoats.emplace_back(std::make_unique<Boat>(
		textures.get("boat"), Owner::Player, sf::Vector2f{ 50.f, 100.f }, "Sea Hag"));

	allBoats.emplace_back(std::make_unique<Boat>(
		textures.get("boat"), Owner::Player, sf::Vector2f{ 25.f, 100.f }, "Sea Biscuit"));

	allActors.emplace_back(std::make_unique<Actor>(
		animationLibrary, textures.get("shadowman")));

	player.setScene(scene.get());
	player.setActivePawn(allActors[0].get());

	loadScene("house.json");

	/*std::ifstream file("assets/scenes/over_world.json");
	if (!file.is_open()) {
		std::cout << "FAILED TO OPEN JSON FILE\n";
	}

	std::string raw((std::istreambuf_iterator<char>(file)),
		std::istreambuf_iterator<char>());

	std::cout << "RAW JSON:\n" << raw << "\n";
	//json j = json::parse(raw);*/
}

void Engine::loadScene(const std::string& path) {
	json j = JsonLoader::load("assets/data/" + path);
	SceneData data = SceneData::fromJson(j);
	scene = std::make_unique<Scene>(textures, animationLibrary, data);
	scene->buildMap(data);
	scene->onEnter(player.getActivePawn());

}

void Engine::run() {
	sf::Clock clock;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		float dt = clock.restart().asSeconds();
		update(dt);
		draw();
	}
}

void Engine::update(float dt) {
	player.update(dt);
	scene->setCameraPos(player.getPawnPos());
	scene->update(dt, player.getActivePawn());
}

void Engine::draw() {
	window.clear();
	scene->draw(window, player.getActivePawn());
	window.display();
}

const AnimationData& Engine::getAnimationData(const std::string& name) const {
	return animationLibrary.get(name);
}