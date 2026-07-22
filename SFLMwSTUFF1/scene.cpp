#include "scene.h"
#include "pawn.h"
#include "textureManager.h"
#include "animationLibrary.h"
#include "townMap.h"
#include <iostream>


Scene::Scene(TextureManager& texture, AnimationLibrary& al, const SceneData& sd)
	: mapType(sd.mapType), textures(texture), animations(al), 
	objInstances(sd.objectInstances),
	objects(sd.objects),
	worldSize(sd.worldSize),
	skyArea(sd.skyArea),
	groundArea(sd.groundArea),
	bottomOffset(sd.bottomOffset),
	skyGradient(sf::Quads, 4),
	groundGradient(sf::Quads, 4),
	skyGrad(sd.skyGradient.enabled),
	groundGrad(sd.groundGradient.enabled){

	camera.setSize(800.f, 600.f);
	
	//buildTilesets(sd);
	buildObjects();
	buildMap();

	if (skyGrad) {
		buildGradient(sd.skyGradient, skyGradient, skyArea);
	}
	if (groundGrad) {
		buildGradient(sd.groundGradient, groundGradient, groundArea);
	}

}

void Scene::update(float dt, Pawn* p) {
	updateCamera(dt, p->getPos());
	updateMovement(dt, p);
	checkBlockingCollision(p);	
	
	//std::cout << "player pos x= " << p->getPos().x << "player pos y= " << p->getPos().y << "\n";
}



void Scene::updateCamera(float dt, sf::Vector2f pawnPos) {
	sf::Vector2f target = pawnPos;
	cameraPos += (target - cameraPos) * cameraSmooth * dt;
	sf::Vector2f half = camera.getSize() * .5f;

	cameraPos.x = std::max(cameraPos.x, half.x);
	cameraPos.x = std::min(cameraPos.x, worldSize.x - half.x);

	cameraPos.y = std::max(cameraPos.y, half.y);
	cameraPos.y = std::min(cameraPos.y, worldSize.y - half.y);

	camera.setCenter(cameraPos);
}

void Scene::draw(sf::RenderWindow& window, Pawn* p) {
	window.setView(camera);
	if (skyGrad)
		window.draw(skyGradient);
	if (groundGrad)
		window.draw(groundGradient);
	if (map)
		map->draw(window);
	if (p) {
		p->draw(window);
	}	
	//if (battleMode)draw more crap
}

void Scene::buildMap() {
	switch (mapType) {
	case MapType::OverWorld:
		//map = std::make_unique<OverworldMap>(tilesets, sd);
		break;

	case MapType::Town:
		map = std::make_unique<TownMap>(objectSprites, objInstances, objects);		
		break;
	case MapType::Battle:
		map = std::make_unique<TownMap>(objectSprites, objInstances, objects);
		break;
	}
}

void Scene::buildObjects() {
	objectSprites.clear();
	objectSprites.reserve(objInstances.size());
	for (const auto& inst : objInstances) {
		//lookup definition
		auto it = objects.find(inst.type);
		if (it == objects.end()) {
			std::cout << "Missing object type: " << inst.type << "\n";
			continue; // skip this objectInstance
		}
		const ObjectData& type = it->second;

		//build sprite
		sf::Sprite sprite;
		sprite.setTexture(textures.get(type.textureName));

		//select variant frame
		sf::IntRect rect(
			inst.variant * type.tileWidth,
			0,
			type.tileWidth,
			type.tileHeight
		);
		sprite.setTextureRect(rect);

		sprite.setPosition(static_cast<float>(inst.x),static_cast<float>(inst.y));	
		//sprite.setOrigin(type.tileWidth / 2, type.tileHeight / 2);
		objectSprites.push_back(sprite);

		if (type.collision) {
			
		}
	}
}

void Scene::onEnter(Pawn* p, sf::Vector2f& pos) {
	p->setWorldBounds(groundArea);
	p->setPos(pos);
	cameraPos = p->getPos();//
}

bool Scene::checkBlockingCollision(Pawn* p) {
	if (!map) return false;
	sf::FloatRect pawnBounds = p->pawnBounds();

	const auto& sprites = map->getObjSprites();
	const auto& instances = map->getObjectInstances();
	const auto& types = map->getObjectData();

	for (size_t i = 0; i < sprites.size(); ++i) {
		const auto& inst = instances[i];
		const auto& type = types.at(inst.type);
		const auto& sprite = sprites[i];
		
		sf::FloatRect objBounds = type.collisionBox;	
		objBounds.left += inst.x;
		objBounds.top += inst.y;

		if (!pawnBounds.intersects(objBounds))
			continue;
	
		if (type.collision) {		
			
			return true;					
		}		
	}
	return false;

	//probably want to split this function into 2.  check blocking collision and check trigger collision.
}





/*
void Scene::buildTilesets(const SceneData& sd) {
	for (auto& [name, info] : sd.tilesets) {
		tilesets.try_emplace(
			name, Tileset(
			textures.get(info.textureName),
			info.tileWidth,
			info.tileHeight)
		);
	}
}*/



void Scene::buildGradient(const GradientData& gd, sf::VertexArray& va, Area& a) {
	va[0].position = { a.topLeft.x, a.topLeft.y };
	va[1].position = { a.bottomRight.x, a.topLeft.y };
	va[2].position = { a.bottomRight.x, a.bottomRight.y };
	va[3].position = { a.topLeft.x, a.bottomRight.y };

	va[0].color = gd.topLeft;
	va[1].color = gd.topRight;
	va[2].color = gd.bottomLeft;
	va[3].color = gd.bottomRight;
}

std::string Scene::consumeSceneChange() {
	std::string s = pendingScene;
	pendingScene.clear();
	return s;
}

