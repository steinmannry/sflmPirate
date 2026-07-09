#pragma once
#include <SFML/Graphics.hpp>


class Tileset {
public:
	Tileset(Tileset&&) = default;
	Tileset& operator=(Tileset&&) = default;
	Tileset(const sf::Texture& tex, int tileW, int tileH);

	const sf::Texture& getTexture() const;
	sf::IntRect getTileRect(int id) const;
	int getTileWidth() { return tileWidth; }
	int getTileHeight() { return tileHeight; }

private:
	const sf::Texture& texture;
	int tileWidth;
	int tileHeight;
};