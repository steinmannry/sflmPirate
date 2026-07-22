#pragma once
#include <SFML/Graphics.hpp>
#include "listBox.h"

class Player;
class Actor;

enum class MenuMode{Party, Command, Item, ItemCommand, DiscardCheck, ItemReceiver};

/*struct ListBox {
	sf::RectangleShape box;
	sf::RectangleShape cursor;
	std::vector<sf::Text> entries;
	int selectedIndex = 0;
	float rowHeight = 30.f;

	void setPosition(float x, float y) {
		box.setPosition(x, y);
		cursor.setPosition(x, y);
		cursor.setFillColor(sf::Color(255, 255, 255, 50)); // transparent white
	}

	void setSize(float w, float h) {
		box.setSize({ w, h });
		cursor.setSize({ w, rowHeight });
	}

	void updateCursor() {
		
		cursor.setPosition(box.getPosition().x, box.getPosition().y + selectedIndex * rowHeight);
	}

	void draw(sf::RenderWindow& window) {
		window.draw(box);

		for (auto& e : entries)
			window.draw(e);
		window.draw(cursor);
	}
};*/


class Menu {
public:
	Menu(Player* p);
	void draw(sf::RenderWindow& window);
	void update(float dt);
	void partySelection(float py);
	void commandSelection(float py);
	void itemSelection(float py);
	void discardCheckSelection(float py);
	void receiverSelection(float py);

	sf::Text makeText(const std::string& s, float x, float y);
	void buildPartyBox();
	void buildReceiverPartyBox();
	void buildCommandBox();	
	void buildDiscardCheck();
	
	void buildMenu();
	
	void buildInventory();
	void buildEquipment();

	bool getCloseRequest() { return closeRequest; }
	void closeRequestFalse() { closeRequest = false; }
	int getPlayerIndex() { return partyBox.selectedIndex; }
private:
	Player* player;
	Actor* selectedActor = nullptr;
	Actor* receiverActor = nullptr;
	float itemWeight = 0.f;
	MenuMode mode = MenuMode::Party;	
	int selectedItemIndex = -1;
	int receiverIndex = -1;
	sf::RectangleShape menuBG;
	ListBox partyBox;
	ListBox commandBox;
	ListBox inventoryBox;
	ListBox discardCheckBox;
	ListBox receiverPartyBox;
	sf::Text discardCheckText;
	sf::RectangleShape equipmentBox;
	sf::RectangleShape itemDescription;
	sf::RectangleShape textWindow;
	std::vector<sf::Text> equipment;
	sf::Font font;
	float inputCooldown = 0.f;
	bool closeRequest = false;
};

