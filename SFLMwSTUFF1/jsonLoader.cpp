#include "jsonLoader.h"
#include <fstream>
#include <iostream>

json JsonLoader::load(const std::string& path) {
	std::ifstream file(path);
	if (!file.is_open()) {
		throw std::runtime_error("failed to open Json file: " + path);
	}
	try {
		return json::parse(file);
	}
	catch (const json::parse_error& e){
	std::cerr << "Json parse error in file: " << path << "\n";
	std::cerr << "message: " << e.what() << "\n";
	return json();
	}

	if (!file.is_open()) {
		std::cerr << "failed to open json file: " << path << "\n";
		return json();
	}

	json j;
	file >> j;
	return j;
	
}