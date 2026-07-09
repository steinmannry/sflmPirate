#pragma once
#include "animation.h"
#include <SFML/Graphics.hpp>

class AnimationData;

class AnimationController {
public:
	AnimationController();
	void update(float dt);
	sf::IntRect  getFrameRect() const;	
	void addAnimation(const std::string& name, const Animation& anim);
	void play(const std::string& name);
private:
	std::map<std::string, Animation> animations;
	std::string current;
};