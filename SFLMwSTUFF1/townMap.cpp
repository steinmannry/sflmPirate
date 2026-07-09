#include "townMap.h"
#include "sceneData.h"
#include "tileset.h"
#include "textureManager.h"
#include <iostream>

TownMap::TownMap(const std::vector<sf::Sprite>& objectSprites, const std::vector<ObjectInstance>& instances, const std::unordered_map<std::string, ObjectData>& data)
	: objectSprites(objectSprites), objInst(instances), objectData(data){
	

	//buildingTileset = &tilesets.at("buildings");
	//others
	//auto& info = tilesetInfo.at("buildings");
	
}


void TownMap::update(float dt) {

}

void TownMap::draw(sf::RenderWindow& window) {
	for (auto& obj : objectSprites) {		
		window.draw(obj);
	}
	//std::cout << "town map draw\n";
}

