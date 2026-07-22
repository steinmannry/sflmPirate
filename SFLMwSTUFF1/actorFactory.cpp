#include "actorFactory.h"
#include "itemFactory.h"
#include "convert.h"
#include "textureManager.h"
#include "animationLibrary.h"
#include <iostream>

std::unordered_map<std::string, ActorData> ActorFactory::actorDB;

void ActorFactory::loadDatabase(const json& j) {
	for (auto& actorJson : j["actors"]) {
		ActorData data = ActorData::fromJson(actorJson);
		actorDB[data.id] = data;
	}
}

const ActorData& ActorFactory::get(const std::string& id) {
	return actorDB.at(id);
}	

std::unique_ptr<Actor> ActorFactory::create(const std::string& id, AnimationLibrary& animLib, TextureManager& tex) {
	const ActorData& data = actorDB.at(id);
	const sf::Texture& texture = tex.get(data.texture);
	//AnimationController& animSet = animLib.get(data.animation);

	auto actor = std::make_unique<Actor>(data, animLib, texture );

	for (const std::string& key : data.animations) {
		const AnimationData& animData = animLib.get(key);

		Animation animObj(
			&texture,
			animData.frameWidth,
			animData.frameHeight,
			animData.frameCount,
			animData.frameTime,
			animData.row,
			animData.loop,
			animData.reverse
		);
		actor->getAnimController().addAnimation(key, animObj);
		actor->getAnimController().play(key);
		actor->getSprite().setOrigin(animData.frameWidth / 2, animData.frameHeight / 2);
	}

	if (!data.equipment.weapon.empty()) {
		std::unique_ptr<Item> item = ItemFactory::create(Convert::itemID(data.equipment.weapon));
		actor->getInventory().getItems().push_back(std::move(item));//push_back tries to copy the unique_ptr, must be moved
		Item* raw = actor->getInventory().getItems().back().get(); //get raw pointer to equip
		actor->getEquipment().equip(raw);
	}
	if (!data.equipment.head.empty()) {
		std::unique_ptr<Item> item = ItemFactory::create(Convert::itemID(data.equipment.head));
		actor->getInventory().getItems().push_back(std::move(item));
		Item* raw = actor->getInventory().getItems().back().get();
		actor->getEquipment().equip(raw);
	}
	if (!data.equipment.armor.empty()) {
		std::unique_ptr<Item> item = ItemFactory::create(Convert::itemID(data.equipment.armor));
		actor->getInventory().getItems().push_back(std::move(item));
		Item* raw = actor->getInventory().getItems().back().get();
		actor->getEquipment().equip(raw);
	}
	if (!data.equipment.hands.empty()) {
		std::unique_ptr<Item> item = ItemFactory::create(Convert::itemID(data.equipment.hands));
		actor->getInventory().getItems().push_back(std::move(item));
		Item* raw = actor->getInventory().getItems().back().get();
		actor->getEquipment().equip(raw);
	}
	if (!data.equipment.feet.empty()) {
		std::unique_ptr<Item> item = ItemFactory::create(Convert::itemID(data.equipment.feet));
		actor->getInventory().getItems().push_back(std::move(item));
		Item* raw = actor->getInventory().getItems().back().get();
		actor->getEquipment().equip(raw);
	}
	if (!data.equipment.misc.empty()) {
		std::unique_ptr<Item> item = ItemFactory::create(Convert::itemID(data.equipment.misc));
		actor->getInventory().getItems().push_back(std::move(item));
		Item* raw = actor->getInventory().getItems().back().get();
		actor->getEquipment().equip(raw);
	}

	for (auto& entry : data.inventory.entries) {
		std::unique_ptr<Item> item = ItemFactory::create(Convert::itemID(entry.id));
		actor->getInventory().addItem(std::move(item), entry.quantity);
	}
	
	return actor;
}

