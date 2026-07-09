#include "tileset.h"

Tileset::Tileset(const sf::Texture& tex, int tileW, int tileH)
	: texture(tex), tileWidth(tileW), tileHeight(tileH) { }

const sf::Texture& Tileset::getTexture() const {
	return texture;
}

sf::IntRect Tileset::getTileRect(int id) const {
	int tilesPerRow = texture.getSize().x / tileWidth;
	int x = (id % (tilesPerRow)) * tileHeight;
	int y = (id / (tilesPerRow)) * tileHeight;
	return sf::IntRect(x, y, tileWidth, tileHeight);
}