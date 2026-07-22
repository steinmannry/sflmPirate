#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "pawn.h"
#include "sceneData.h"
#include "animationData.h"
#include "map.h"
#include "area.h"
#include "tileset.h"

class AnimationLibrary;
class TextureManager;
class Pawn;
class Boat;
class Actor;

class Scene{
public:
	virtual ~Scene() = default;
	Scene(TextureManager& texture, AnimationLibrary& al, const SceneData& sd);
	std::unique_ptr<Map> map;
	std::function<void(const std::string&)> requestSceneChange;

	virtual void update(float dt, Pawn* p);	
	virtual void draw(sf::RenderWindow& window, Pawn* p);
	bool checkBlockingCollision(Pawn* p);
	std::string consumeSceneChange();
	void buildMap();
	void onEnter(Pawn* p, sf::Vector2f& pos);//override
	virtual void onBattleEnter(std::vector<Actor*> crew, sf::Vector2f pos, std::vector<Actor*> enemies) {}

	bool hasPendingSceneChange() const { return !pendingScene.empty(); }
	void setCameraPos(sf::Vector2f pos) { cameraPos = pos; }

protected: 
	virtual void updateMovement(float dt, Pawn* p) {}
	
	void buildObjects();
	//void buildTilesets(const SceneData& sd);
	
	
	

	void buildGradient(const GradientData& gd, sf::VertexArray& va, Area& a);

	//void setActivePawn(Pawn* p);
	
	void updateCamera(float dt, sf::Vector2f camPos);//override

	

	
	MapType mapType;
	TextureManager& textures;
	AnimationLibrary& animations;
	//std::unordered_map<std::string, Tileset> tilesets;
	std::vector<sf::Sprite> objectSprites;
	std::vector<ObjectInstance> objInstances;
	std::unordered_map<std::string, ObjectData> objects;

	int selectedIndex = 0;
	//Pawn* activePawn = nullptr;
	//std::vector<Boat*> enemyBoats;


	sf::Vector2f worldSize;
	Area skyArea;
	Area groundArea;
	
	Area bottomOffset;
	sf::VertexArray skyGradient;
	sf::VertexArray groundGradient;
	bool skyGrad = false;
	bool groundGrad = true;

	sf::View camera;
	sf::Vector2f cameraPos;
	float cameraSmooth = 1.f;

	std::string pendingScene;


	
};