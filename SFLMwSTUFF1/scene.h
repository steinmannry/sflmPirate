#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "playerPawn.h"
#include "sceneData.h"
#include "animationData.h"
#include "map.h"
#include "area.h"
#include "tileset.h"

class AnimationLibrary;
class TextureManager;
class PlayerPawn;
class Boat;

class Scene {
public:
	Scene(TextureManager& texture, AnimationLibrary& al, const SceneData& sd);
	std::unique_ptr<Map> map;
	std::function<void(const std::string&)> requestSceneChange;

	void buildMap();
	void buildObjects();
	//void buildTilesets(const SceneData& sd);
	void onEnter(PlayerPawn* p, sf::Vector2f pos);
	void checkCollision(PlayerPawn* p);
	void buildGradient(const GradientData& gd, sf::VertexArray& va, Area& a);

	//void setActivePawn(PlayerPawn* p);
	void setCameraPos(sf::Vector2f pos) { cameraPos = pos; }
	void updateCamera(float dt, sf::Vector2f camPos);

	void update(float dt, PlayerPawn* p);
	void draw(sf::RenderWindow& window, PlayerPawn* p);


private:
	MapType mapType;
	TextureManager& textures;
	AnimationLibrary& animations;
	std::unordered_map<std::string, Tileset> tilesets;
	std::vector<sf::Sprite> objectSprites;
	std::vector<ObjectInstance> objInstances;
	std::unordered_map<std::string, ObjectData> objects;

	int selectedIndex = 0;
	//PlayerPawn* activePawn = nullptr;
	std::vector<Boat*> enemyBoats;


	sf::Vector2f worldSize;
	Area groundArea;
	Area skyArea;
	Area bottomOffset;
	sf::VertexArray skyGradient;
	sf::VertexArray groundGradient;
	bool skyGrad = false;
	bool groundGrad = true;

	sf::View camera;
	sf::Vector2f cameraPos;
	float cameraSmooth = 1.f;

};