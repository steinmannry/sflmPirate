#include "engine.h"
#include "scene.h"
#include "sceneData.h"
#include "jsonLoader.h"
#include "itemFactory.h"
#include "actorFactory.h"
#include "boat.h"
#include "actor.h"
#include <fstream>
#include <iostream>


Engine::~Engine() = default;

Engine::Engine()
	: window(sf::VideoMode(800, 600), "aaaargh!"){
	
	loadTextures();
	init();	

	animationLibrary.load("walkRL", "walk_rl.json");	
	
	player.getCrew().emplace_back(ActorFactory::create("JaySan", animationLibrary, textures));
	player.getCrew().emplace_back(ActorFactory::create("MC", animationLibrary, textures));
	player.setActivePawn(player.getCrew()[0].get());
	menu = std::make_unique<Menu>(&player);

	/*allBoats.emplace_back(std::make_unique<Boat>(
		textures.get("boat"), Owner::Player, sf::Vector2f{ 50.f, 100.f }, "Sea Hag"));

	allBoats.emplace_back(std::make_unique<Boat>(
		textures.get("boat"), Owner::Player, sf::Vector2f{ 25.f, 100.f }, "Sea Biscuit"));

	allActors.emplace_back(std::make_unique<Actor>(
		animationLibrary, textures.get("shadowman")));*/	
	
	

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

void Engine::init() {	
	json weaponsJson = JsonLoader::load("assets/data/items/weapons.json");
	json armorJson = JsonLoader::load("assets/data/items/armor.json");
	json consumableJson = JsonLoader::load("assets/data/items/consumable.json");
	json actorJson = JsonLoader::load("assets/data/actors/actors.json");
	
	ItemFactory::loadDatabase(weaponsJson);
	ItemFactory::loadDatabase(armorJson);
	ItemFactory::loadDatabase(consumableJson);
	ActorFactory::loadDatabase(actorJson);
}

void Engine::loadTextures() {
	textures.load("ocean", "waves2.png");
	textures.load("boat", "boat_right.png");
	textures.load("house", "house.png");
	textures.load("wildflowers", "wildflowers.png");	
	textures.load("sign", "sign.png");	
	textures.load("largePine", "largePine.png");

	textures.load("shadowman", "shadowman.png");
	textures.load("jay", "archee.png");
}

void Engine::loadScene(const std::string& path) {

	json j = JsonLoader::load("assets/data/scene/" + path);
	SceneData data = SceneData::fromJson(j);

	scene = std::make_unique<Scene>(textures, animationLibrary, data);
	scene->buildMap();

	scene->requestSceneChange = [this](const std::string& path) {
		loadScene(path);
	};

	player.setScene(scene.get());
	player.getActivePawn()->setScene(scene.get());
	//player.getActivePawn()->update()
	
	scene->onEnter(player.getActivePawn(), data.spawnPos);
	//player.getActivePawn()->getSprite().setPosition(data.spawnPos);
	

	std::cout << data.sceneName << " " << data.spawnPos.x << data.spawnPos.y << "\n";
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

	if (state == GameState::Menu) {
		menu->update(dt);
		if (menu->getCloseRequest()) {
			menu->closeRequestFalse();
			player.resumeGame();
			state = GameState::Game;			
		}
	}

	if (state == GameState::Game) {
		scene->setCameraPos(player.getPawnPos());
		scene->update(dt, player.getActivePawn());
		player.update(dt);

		if (scene->hasPendingSceneChange()) {
			std::string next = scene->consumeSceneChange();
			loadScene(next);
		}
		player.requestStateChange = [&](GameState s) {
			state = s;
		};

	}	
}

void Engine::draw() {
	if (state == GameState::Game) {
		window.clear();
		scene->draw(window, player.getActivePawn());
		window.display();
	}

	if (state == GameState::Menu) {
		window.clear();
		menu->draw(window);
		window.display();
	}
}

const AnimationData& Engine::getAnimationData(const std::string& name) const {
	return animationLibrary.get(name);
}