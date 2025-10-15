#pragma once

#include "Brick.h"

class BrickParticle : public Brick
{
public:
	BrickParticle();

	bool isOnScreen() const;
	void update(float dt);
	void set(sf::Vector2f pos, float angularVelocity);
	void setSize(sf::Vector2f size);

private:
	static constexpr float FALL_SPEED = 400;
	static constexpr std::uint8_t ALPHA = 160;
	float _angularVelocity = 40;
};

