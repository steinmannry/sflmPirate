#pragma once
#include <SFML/Graphics.hpp>
#include "animationController.h"

class Scene;

class Ocean {
public:
	Ocean(Scene& scene);

private:
	sf::Sprite sprite;
	AnimationController anim;

};