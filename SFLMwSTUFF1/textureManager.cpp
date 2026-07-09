#include "textureManager.h"

void TextureManager::load(const std::string& name, const std::string& path) {
	sf::Texture texture;
	texture.loadFromFile("assets/textures/" + path);
	textures[name] = std::move(texture);
}