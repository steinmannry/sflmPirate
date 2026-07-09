#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>

class TextureManager {
public:
	const sf::Texture& get(const std::string& name) {
		return textures.at(name);
	}

	void load(const std::string& name, const std::string& path);

private:
	std::unordered_map<std::string, sf::Texture> textures;
		
};
