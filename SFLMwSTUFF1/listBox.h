#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

struct ListBox {
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
};