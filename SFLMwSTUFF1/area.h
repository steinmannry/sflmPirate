#pragma once
#include <SFML/Graphics.hpp>

struct Area {
	sf::Vector2f topLeft; //world space coordinates
	sf::Vector2f bottomRight;

	Area() = default;
	Area(sf::Vector2f tl, sf::Vector2f br);

	sf::Vector2f size() const {
		return { bottomRight.x - topLeft.x, bottomRight.y - topLeft.y };
	}

	float width() const { return bottomRight.x - topLeft.x; }
	float height() const { return bottomRight.y - topLeft.y; }

	sf::FloatRect toRect() const {
		return {topLeft.x, topLeft.y, width(), height()};
	}
};