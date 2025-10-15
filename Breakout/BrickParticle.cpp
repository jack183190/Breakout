#include "BrickParticle.h"
#include "CONSTANTS.h"

BrickParticle::BrickParticle()
	: Brick(0, FLT_MAX, 0, 0)
{
	sf::Color color = _shape.getFillColor();
	color.a = ALPHA;
	_shape.setFillColor(color);
}

bool BrickParticle::isOnScreen() const
{
	return _shape.getPosition().y < WINDOW_HEIGHT + 200;
}

void BrickParticle::update(float dt) {
	sf::Vector2f pos = _shape.getPosition();
	pos.y += dt * FALL_SPEED;
	_shape.setPosition(pos);

	float rot = _shape.getRotation() + dt * _angularVelocity;
	_shape.setRotation(rot);
}

void BrickParticle::set(sf::Vector2f pos, float angularVelocity)
{
	_shape.setPosition(pos);
	_shape.setRotation(0);
	_angularVelocity = angularVelocity;
}

void BrickParticle::setSize(sf::Vector2f size) {
	_shape.setSize(size);
}