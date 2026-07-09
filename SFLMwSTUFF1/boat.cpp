#include "boat.h"
#include <iostream>

Boat::Boat(const sf::Texture& tex, Owner o, const sf::Vector2f pos, const std::string& n)
	: PlayerPawn(), owner(o), name(n){

	sprite.setTexture(tex);
	sprite.setScale(.2f, .2f);
	sprite.setPosition(pos);
	auto size = sprite.getTexture()->getSize();
	sprite.setOrigin(size.x / 2.f, size.y / 2.f);
	sprite.setRotation(0.f);
}

void Boat::update(float dt) {
	sprite.rotate(rotationSpeed * dt);
	
	float rad = (sprite.getRotation()) * (3.14159f / 180.f);
	sf::Vector2f forward(std::cos(rad), std::sin(rad) );

	if (throttle) {		
		velocity += forward * (thrustPower / mass) * dt;

		std::cout << "rotation: " << sprite.getRotation() << "\n"
			<< "forward: " << forward.x << ", " << forward.y << "\n";
	}
	velocity *= std::pow(.90f, dt * 60.f);//drag
	sprite.move(velocity);

	sf::Vector2f pos = sprite.getPosition();
	
	pos.x = std::clamp(pos.x, worldBounds.topLeft.x, worldBounds.bottomRight.x);
	pos.y = std::clamp(pos.y, worldBounds.topLeft.x, worldBounds.bottomRight.x);
	sprite.setPosition(pos.x, pos.y);
}

void Boat::draw(sf::RenderWindow& window) {
	window.draw(sprite);
}

sf::Vector2f Boat::getPos() const {
	return sprite.getPosition();
}

void Boat::handleInput() {
	if (sf::Joystick::isConnected(0)) {
		float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);

		if (std::abs(x) > 15.f)
			setRotationSpeed(x);
		else
			setRotationSpeed(0);

		if (sf::Joystick::isButtonPressed(0, 0)) {
			setThrottle(true);
		}
		else
			setThrottle(false);
	}
}

sf::FloatRect Boat::pawnBounds() {
	return sprite.getGlobalBounds();
}