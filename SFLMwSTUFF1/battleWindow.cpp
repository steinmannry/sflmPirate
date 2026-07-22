#include "battleWindow.h"



void BattleWindow::draw(sf::RenderWindow& window) {
	commandList.draw(window);
}

void BattleWindow::update(float dt) {
	inputCooldown -= dt;
	if (inputCooldown < 0.f)
		inputCooldown = 0.f;
	if (inputCooldown == 0.f) {
		if (sf::Joystick::isConnected(0)) {
			float px = sf::Joystick::getAxisPosition(0, sf::Joystick::PovX);//rl
			float py = sf::Joystick::getAxisPosition(0, sf::Joystick::PovY);//ud

			commandSelection(py);
			if (command == Command::Move) {
				return;
			}

			if (command == Command::Attack) {
				return;
			}
		}

	}
}

void BattleWindow::commandSelection(float py) {
	if (py > 50) {// up
		commandList.selectedIndex = std::max(commandList.selectedIndex - 1, 0);
		commandList.updateCursor();
		inputCooldown = .2f;
	}
	if (py < -50) {  // down
		commandList.selectedIndex = std::min(commandList.selectedIndex + 1, static_cast<int>(commandList.entries.size()) - 1);
		commandList.updateCursor();
		inputCooldown = .2f;
	}

	if (sf::Joystick::isButtonPressed(0, 0)) {

		//-------------MOVE-------------
		if (commandList.selectedIndex == 0) {
			command = Command::Move;
			return;
		}

		//------------ATTACK---------------
		if (commandList.selectedIndex == 1) {
			
		}



		//------------ITEM-----------------



		//-----------DEFEND----------------
	}
}



void BattleWindow::buildNameBox(std::string& n) {
	nameBox.setSize({ 200.f, 40.f });
	nameBox.setFillColor(sf::Color(0, 0, 0, 125));
	nameBox.setPosition({ 0.f, 460.f });
	nameBox.setOutlineThickness(2.f);
	nameBox.setOutlineColor(sf::Color::White);
	sf::Text name;
	name.setFont(font);
	name.setFillColor(sf::Color::White);
	name.setString(n);
	name.setPosition({ 10.f, 465.f });
}


void BattleWindow::buildCommandWindow() {
	commandList.setSize(200.f, 200.f);
	commandList.box.setFillColor(sf::Color(0, 0, 0, 125));
	commandList.box.setOutlineThickness(2.f);
	commandList.box.setOutlineColor(sf::Color::White);
	commandList.setPosition(0.f, 400.f);
	commandList.rowHeight = 30.f;

	commandList.entries.clear();
	commandList.selectedIndex = 0;

	float startX = commandList.box.getPosition().x + 10.f;
	float startY = commandList.box.getPosition().y + 0.f;

	commandList.entries.push_back(makeText("Move", startX, startY + 0 * commandList.rowHeight));
	commandList.entries.push_back(makeText("Attack", startX, startY + 1 * commandList.rowHeight));
	commandList.entries.push_back(makeText("Item", startX, startY + 2 * commandList.rowHeight));
	commandList.entries.push_back(makeText("Defend", startX, startY + 3 * commandList.rowHeight));
}

sf::Text BattleWindow::makeText(const std::string& s, float x, float y) {
	font.loadFromFile("assets/arial.ttf");
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White);
	text.setString(s);
	text.setPosition(x, y);
	return text;
}