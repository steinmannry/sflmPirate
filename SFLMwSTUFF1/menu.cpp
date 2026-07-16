#include "menu.h"
#include "player.h"
#include "actor.h"
#include "inventory.h"

#include <iostream>

Menu::Menu(Player* p) : player(p){
	font.loadFromFile("assets/arial.ttf");
	auto& crew = player->getCrew();
	if (crew.empty()) return;
	buildMenu();
	buildPartyBox();

	
	std::cout << "crew size = " << crew.size()
		<< ", selectedIndex = " << partyBox.selectedIndex << "\n";

	if (crew.empty() || partyBox.selectedIndex >= crew.size()) {
		std::cout << "Invalid selection!\n";
	}
	else {
		selectedActor = crew[partyBox.selectedIndex].get();
	}
}

void Menu::update(float dt) {
	sf::Joystick::update();
	inputCooldown -= dt;
	if (inputCooldown < 0.f)
		inputCooldown = 0.f;
	if (inputCooldown == 0.f) {
		if (sf::Joystick::isConnected(0)) {

			if (sf::Joystick::isButtonPressed(0, 3)) {
				closeRequest = true;
				inputCooldown = .2f;
				return;
			}
			if (closeRequest)
				return;

			float px = sf::Joystick::getAxisPosition(0, sf::Joystick::PovX);//rl
			float py = sf::Joystick::getAxisPosition(0, sf::Joystick::PovY);//ud

			
			switch (mode) {
			case MenuMode::Party:
				partySelection(py);
				break;
			case MenuMode::Command:
				commandSelection(py);
				break;
			case MenuMode::Item:
				itemSelection(py);
				break;
			case MenuMode::ItemCommand:
				commandSelection(py);
				break;
			case MenuMode::DiscardCheck:
				discardCheckSelection(py);
				break;
			}
		}
	}
}
void Menu::draw(sf::RenderWindow& window) {
	window.draw(menuBG);
	partyBox.draw(window);
	commandBox.draw(window);
	if (mode == MenuMode::Item) {
		window.draw(equipmentBox);
		for (auto& e : equipment) {
			window.draw(e);
		}
		inventoryBox.draw(window);
	}
	if (mode == MenuMode::DiscardCheck) {
		discardCheckBox.draw(window);
		window.draw(discardCheckText);
	}

}

void Menu::discardCheckSelection(float py) {
	if (py > 50) {// up
		discardCheckBox.selectedIndex = std::max(discardCheckBox.selectedIndex - 1, 0);
		discardCheckBox.updateCursor();
		inputCooldown = .2f;
	}
	if (py < -50) {  // down
		discardCheckBox.selectedIndex = std::min(discardCheckBox.selectedIndex + 1, static_cast<int>(discardCheckBox.entries.size()) - 1);
		discardCheckBox.updateCursor();
		inputCooldown = .2f;
	}


	if (sf::Joystick::isButtonPressed(0, 0)) {
		if (discardCheckBox.selectedIndex == 0) {
			selectedActor->getEquipment().unequip(selectedActor->getInventory().getItem(selectedItemIndex));
			selectedActor->getInventory().removeItemByIndex(selectedItemIndex, 1);
			inputCooldown = .2f;
			buildEquipment();
			buildInventory();
			mode = MenuMode::Item;
		}
		if (discardCheckBox.selectedIndex == 1) {
			inputCooldown = .2f;
			mode = MenuMode::Item;
		}
	}

}

void Menu::partySelection(float py) {
	if (py > 50) {// up
		partyBox.selectedIndex = std::max(partyBox.selectedIndex - 1, 0);
		partyBox.updateCursor();
		inputCooldown = .2f;
	}
	if (py < -50) {  // down
		partyBox.selectedIndex = std::min(partyBox.selectedIndex + 1, static_cast<int>(partyBox.entries.size()) - 1);
		partyBox.updateCursor();
		inputCooldown = .2f;
	}

	//----------EXIT
	if (sf::Joystick::isButtonPressed(0, 1)) {
		closeRequest = true;
		inputCooldown = .2f;
	}
	//----------SELECT-ACTOR-------------
	if (sf::Joystick::isButtonPressed(0, 0)) {
		if (player->getCrew().empty() || partyBox.selectedIndex >= player->getCrew().size()) {
			std::cout << "no crew\n";
		}
		else {
			selectedActor = player->getCrew()[partyBox.selectedIndex].get();//use .get() to extract unique_ptr
			inputCooldown = .2f;
			mode = MenuMode::Command;
			buildCommandBox();			
		}
	}
}

void Menu::itemSelection(float py) {
	if (py > 50) {// up
		inventoryBox.selectedIndex = std::max(inventoryBox.selectedIndex - 1, 0);
		inventoryBox.updateCursor();
		inputCooldown = .2f;
	}
	if (py < -50) {  // down
		inventoryBox.selectedIndex = std::min(inventoryBox.selectedIndex + 1, static_cast<int>(inventoryBox.entries.size()) - 1);
		inventoryBox.updateCursor();
		inputCooldown = .2f;
	}
	

	//---------SELECT-ITEM-----------------
	if (sf::Joystick::isButtonPressed(0, 0)) {
		selectedItemIndex = inventoryBox.selectedIndex;
		mode = MenuMode::ItemCommand;	
		buildCommandBox();
		inputCooldown = .2f;		
	}
	//----------BACK TO ACTOR COMMAND-----------
	if (sf::Joystick::isButtonPressed(0, 1)) {
		mode = MenuMode::Command;
		buildCommandBox();
		inputCooldown = .2f;
	}


}

void Menu::commandSelection(float py) {
	if (py > 50) {// up
		commandBox.selectedIndex = std::max(commandBox.selectedIndex - 1, 0);
		commandBox.updateCursor();
		inputCooldown = .2f;
	}
	if (py < -50) {  // down
		commandBox.selectedIndex = std::min(commandBox.selectedIndex + 1, static_cast<int>(commandBox.entries.size()) - 1);
		commandBox.updateCursor();
		inputCooldown = .2f;
	}

	

	//-----------ACTOR--COMMANDS-------------------
	if (mode == MenuMode::Command) {
		if (sf::Joystick::isButtonPressed(0, 0)) {
			if (commandBox.selectedIndex == 0) {
				mode = MenuMode::Item;
				buildEquipment();
				buildInventory();
				inputCooldown = .2f;
			}
		}

		//-------BACK TO PARTY SELECTION----------
		if (sf::Joystick::isButtonPressed(0, 1)) {
			mode = MenuMode::Party;
			inputCooldown = .2f;
		}
	}

	//--------------ITEM --COMMANDS-----------
	if (mode == MenuMode::ItemCommand) {
		
		if (sf::Joystick::isButtonPressed(0, 0)) {
			//-----------USE/Equip-----------
			if (commandBox.selectedIndex == 0) {
				inputCooldown = .2f;
			}

			//-----------DISCARD----------
			if (commandBox.selectedIndex == 1) {
				inputCooldown = .2f;
				Item* item = selectedActor->getInventory().getItem(selectedItemIndex);


				if (item->getType() == ItemType::Weapon || item->getType() == ItemType::Armor) {
					if (selectedActor->getEquipment().isEquipped(item)) {
						buildDiscardCheck();
						mode = MenuMode::DiscardCheck;
						return;
					}
					selectedActor->getEquipment().unequip(selectedActor->getInventory().getItem(selectedItemIndex));
					selectedActor->getInventory().removeItemByIndex(selectedItemIndex, 1);			
					buildEquipment();
					mode = MenuMode::Item;
				}
				else 
					selectedActor->getInventory().removeItemByIndex(selectedItemIndex, item->getQuantity());
				buildInventory();
				mode = MenuMode::Item;
			}


			//-----------EXIT------------
			if (commandBox.selectedIndex == 2) {
				mode = MenuMode::Item;
				inputCooldown = .2f;
			}
		}
		
	}
}


void Menu::buildDiscardCheck() {
	discardCheckBox.setSize(550.f, 200.f);
	discardCheckBox.box.setFillColor(sf::Color::Black);
	discardCheckBox.box.setOutlineColor(sf::Color::Red);
	discardCheckBox.box.setOutlineThickness(4.f);
	discardCheckBox.setPosition(200.f, 200.f);
	discardCheckBox.rowHeight = 30.f;

	float x = discardCheckBox.box.getPosition().x + 10.f;
	float y = discardCheckBox.box.getPosition().y;
	discardCheckText = makeText("Are you sure you would like to discard equipped item?", 210.f, 360.f);

	discardCheckBox.entries.clear();
	discardCheckBox.entries.push_back(makeText("Yes", x, y + 0 * discardCheckBox.rowHeight));
	discardCheckBox.entries.push_back(makeText("No", x, y + 1 * discardCheckBox.rowHeight));
	
	discardCheckBox.cursor.setPosition(x, y);
}

void Menu::buildInventory() {
	inventoryBox.setSize(250.f, 350.f);
	inventoryBox.box.setFillColor(sf::Color::Black);
	inventoryBox.box.setOutlineThickness(2.f);
	inventoryBox.setPosition(275.f, 10.f);
	inventoryBox.rowHeight = 30.f;

	inventoryBox.entries.clear();
	float startX = inventoryBox.box.getPosition().x + 10.f;
	float startY = inventoryBox.box.getPosition().y + 0.f;

	Inventory& inv = selectedActor->getInventory();
	if (!inv.getItems().empty()) {
		for (size_t i = 0; i < inv.getItems().size(); ++i) {
			std::string n = inv.getItem(i)->getName() + "  x " + std::to_string(inv.getItem(i)->getQuantity());
			inventoryBox.entries.push_back(makeText(n, startX, startY + i * inventoryBox.rowHeight));
		}
	}
	else
		inventoryBox.entries.push_back(makeText("inventory empty ", startX, startY));

}

void Menu::buildEquipment() {
	equipment.clear();
	float rowHeight = 30.f;
	equipmentBox.setSize({ 300.f, 300.f });
	equipmentBox.setFillColor(sf::Color::Black);
	equipmentBox.setOutlineThickness(2.f);
	equipmentBox.setPosition(10.f, 10.f + (getPlayerIndex() +1) * rowHeight);
	
	float x = equipmentBox.getPosition().x + 10.f;
	float y = equipmentBox.getPosition().y + 10.f;
	
	Equipment& eq = selectedActor->getEquipment();
	auto equipped = eq.getEquippedList();


	for (size_t i = 0; i < equipped.size(); ++i) {
		const auto& [slotName, item] = equipped[i];

		std::string text = slotName + ": ";
		if (item)
			text += item->getName();
		else
			text += "None";

		equipment.emplace_back(makeText(text, x, y + i * rowHeight));
	}
}


sf::Text Menu::makeText(const std::string& s, float x, float y) {
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White);
	text.setString(s);
	text.setPosition(x, y);
	return text;
}

void Menu::buildCommandBox(){
	commandBox.setSize(250.f, 150.f);
	commandBox.box.setFillColor(sf::Color::Black);
	commandBox.box.setOutlineThickness(2.f);
	commandBox.setPosition(10.f, 450.f);
	commandBox.rowHeight = 30.f; 

	commandBox.entries.clear();
	float startX = commandBox.box.getPosition().x + 10.f;
	float startY = commandBox.box.getPosition().y + 0.f;

	if (mode == MenuMode::Command) {
		commandBox.entries.push_back(makeText("Items", startX, startY + 0 * commandBox.rowHeight));
		commandBox.entries.push_back(makeText("Stats", startX, startY + 1 * commandBox.rowHeight));
		commandBox.entries.push_back(makeText("Back", startX, startY + 2 * commandBox.rowHeight));
	}

	if (mode == MenuMode::ItemCommand){
		commandBox.entries.push_back(makeText("Use/Equip", startX, startY + 0 * commandBox.rowHeight));
		commandBox.entries.push_back(makeText("Discard", startX, startY + 1 * commandBox.rowHeight));
		commandBox.entries.push_back(makeText("Back", startX, startY + 2 * commandBox.rowHeight));
	}


}


void Menu::buildPartyBox() {
	partyBox.setSize( 250.f, 300.f );
	partyBox.box.setFillColor(sf::Color::Black);
	partyBox.box.setOutlineThickness(2.f);
	partyBox.box.setOutlineColor(sf::Color::White);

	float startX = partyBox.box.getPosition().x + 10;
	float startY = partyBox.box.getPosition().y + 10;

	partyBox.setPosition(startX, startY);
	partyBox.rowHeight = 30.f;
	
	partyBox.entries.clear();
	int playerIndex = 0;

	for (auto& actor : player->getCrew()) {
		sf::Text t;
		t.setFont(font);
		t.setCharacterSize(24);
		t.setFillColor(sf::Color::White);
		t.setString(actor->getName());
		t.setPosition(startX + 10.f, startY + playerIndex * partyBox.rowHeight);
		partyBox.entries.push_back(t);
		playerIndex++;
	}	
}

void Menu::buildMenu() {
	menuBG.setSize({ 800.f, 600.f });
	menuBG.setOutlineThickness(2.f);
	menuBG.setOutlineColor(sf::Color::White);
	menuBG.setFillColor(sf::Color::Black);
	menuBG.setPosition(0.f, 0.f);
}

/*
cursor.setSize({ 250.f, 30.f }); // width matches partyList, height matches one row
cursor.setFillColor(sf::Color(255, 255, 255, 50)); // transparent white
cursor.setOutlineThickness(1.f);
cursor.setOutlineColor(sf::Color::White);

setCursorPosition();*/