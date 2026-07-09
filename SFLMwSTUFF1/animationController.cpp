#include "animationController.h"
#include <iostream>

AnimationController::AnimationController() {}

sf::IntRect AnimationController::getFrameRect() const {
	const Animation anim = animations.at(current);

	int left = anim.currentFrame * anim.frameWidth;
	int top = anim.row * anim.frameHeight;
	return sf::IntRect(left, top, anim.frameWidth, anim.frameHeight);
}

void AnimationController::update(float dt) {
	//std::cout << "Current animation: '" << current << "'\n";

	Animation& anim = animations[current];
	
	anim.timer += dt;
	if (anim.timer >= anim.frameTime) {
		anim.timer -= anim.frameTime;
		anim.currentFrame++;

		if (anim.currentFrame >= anim.frameCount) {
			anim.currentFrame = anim.loop ? 0 : anim.frameCount - 1;
		}
	}
}

void AnimationController::addAnimation(const std::string& name, const Animation& anim) {
	animations[name] = anim;
	std::cout << "Added animation: '" << name << "'\n";

	//if first anim added, auto select it.
	if (current.empty()) {
		current = name;
	}
}

void AnimationController::play(const std::string& name) {
	if (current == name)
		return;

	current = name;

	//reset state
	Animation& anim = animations[current];
	anim.currentFrame = 0;
	anim.timer = 0.f;
}