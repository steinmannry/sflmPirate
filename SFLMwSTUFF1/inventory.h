#pragma once
#include <SFML/Graphics.hpp>
#include "item.h"

class Actor;

class Inventory {
public:
	Inventory() = default;
	//disable copying
	Inventory(const Inventory&) = delete;
	Inventory& operator=(const Inventory&) = delete;
	//enable moving
	Inventory(Inventory&&) = default;
	Inventory& operator=(Inventory&&) = default;

	void draw(sf::RenderWindow& window);
	void update(float dt);
	void setOwner(Actor* a) { owner = a; }	

	const Item* getItem(int x) const { return items[x].get(); }
	Item* getItem(int x) { return items[x].get(); }
	std::vector<std::unique_ptr<Item>>& getItems() { return items; }
	float getWeight()  { return weight; }
	bool addItem(std::unique_ptr<Item> item, int q);	
	std::unique_ptr<Item> extractItem(int index);
	void removeItem(Item& item);
	void removeItemByIndex(size_t x, size_t q);
	void useItem(size_t x);
	



private:
	Actor* owner = nullptr;
	std::vector<std::unique_ptr<Item>> items;
	float weight = 0.f;

	

};
