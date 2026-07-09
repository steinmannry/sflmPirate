#pragma once
#include <SFML/Graphics.hpp>
#include "jsonLoader.h"
#include "sceneData.h"
#include "tileset.h"

//class Tileset;


class Map {
public:
	virtual ~Map() = default;
	//virtual void load(const json& j) = 0;
	virtual void update(float dt) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual const std::unordered_map<std::string, ObjectData>& getObjectData() const = 0;
	virtual const std::vector<sf::Sprite>& getObjSprites() const = 0;
	virtual const std::vector<ObjectInstance>& getObjectInstances() const = 0;

};