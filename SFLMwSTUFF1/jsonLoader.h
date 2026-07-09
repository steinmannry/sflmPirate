#pragma once
#include "include/json.hpp"

using json = nlohmann::json;

class JsonLoader {
public:
	static json load(const std::string& path);
};