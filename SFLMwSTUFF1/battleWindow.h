#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "listBox.h"

enum class Command{Move, Attack, Item, Defend};

class BattleWindow {
public:
	void update(float dt);
	void draw(sf::RenderWindow& window);
	void commandSelection(float py);

	Command getCommand() { return command;  }
	void buildNameBox(std::string& n);
	void buildCommandWindow();
	sf::Text makeText(const std::string& s, float x, float y);
private:
	ListBox commandList;
	sf::RectangleShape nameBox;
	sf::Font font;
	float inputCooldown = 0.f;
	Command command = Command::Move;
};
