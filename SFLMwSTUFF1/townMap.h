#pragma once
#include "map.h"
#include <SFML/Graphics.hpp>

class TextureManager;

class TownMap : public Map {
public: 
	//TownMap(std::unordered_map<std::string, Tileset>& tilesets, const SceneData& sd);
	TownMap(const std::vector<sf::Sprite>& objectSprites, const std::vector<ObjectInstance>& instances, const std::unordered_map<std::string, ObjectData>& data );
	void update(float dt) override;
	void draw(sf::RenderWindow& window) override;

	const std::unordered_map<std::string, ObjectData>& getObjectData() const override { return objectData; }
	const std::vector<sf::Sprite>& getObjSprites() const override { return objectSprites; }
	const std::vector<ObjectInstance>& getObjectInstances() const override { return objInst; }

	//void drawLayer(sf::RenderWindow& window, const std::vector<int>& layer, const Tileset& tileset);
	//void generateRandomObjects(ObjectInstance oi);
private:
	//sf::Sprite sprite;
	
	//std::unordered_map<std::string, Tileset>& tilesets;
	std::unordered_map<std::string, ObjectData> objectData;
	const std::vector<ObjectInstance> objInst;
	const std::vector<sf::Sprite>objectSprites;
	int width;
	int height;

	std::vector<int> groundLayer;
	//std::vector<int> buildingLayer;

	//Tileset* groundTileset;
	//Tileset* buildingTileset;
	//vector of actors, npc's
};