#include "Ball.h"
#include "GameManager.h" // avoid cicular dependencies
#include <iostream>

Ball::Ball(sf::RenderWindow* window, float velocity, GameManager* gameManager)
	: _window(window), _velocity(velocity), _gameManager(gameManager),
	_timeWithPowerupEffect(0.f), _isFireBall(false), _isAlive(true), _direction({ 1,1 }), _ballBounceSound(AssetManager::Singleton().ballBounceSound)
{
	_sprite.setRadius(RADIUS);
	_sprite.setFillColor(sf::Color::Cyan);
	_sprite.setPosition(0, 300);
	resetPitch();

	// start with no trail
	for (sf::CircleShape& trail : _trails) {
		trail.setFillColor(sf::Color::Transparent);
		trail.setRadius(RADIUS);
	}
}

Ball::~Ball()
{
}

void Ball::update(float dt)
{
	updateTrail(dt);

	// check for powerup, tick down or correct
	if (_timeWithPowerupEffect > 0.f)
	{
		_timeWithPowerupEffect -= dt;
	}
	else
	{
		if (_velocity != VELOCITY)
			_velocity = VELOCITY;   // reset speed.
		else
		{
			setFireBall(0);    // disable fireball
			_sprite.setFillColor(sf::Color::Cyan);  // back to normal colour.
		}
	}

	// Fireball effect
	if (_isFireBall)
	{
		// Flickering effect
		int flicker = rand() % 50 + 205; // Random value between 205 and 255
		_sprite.setFillColor(sf::Color(flicker, flicker / 2, 0)); // Orange flickering color
	}

	// Update position with a subtle floating-point error
	_sprite.move(_direction * _velocity * dt);

	// check bounds and bounce
	sf::Vector2f position = _sprite.getPosition();
	sf::Vector2u windowDimensions = _window->getSize();

	// bounce on walls
	if ((position.x >= windowDimensions.x - 2 * RADIUS && _direction.x > 0) || (position.x <= 0 && _direction.x < 0))
	{
		_direction.x *= -1;
		playSound();
	}

	// bounce on ceiling
	if (position.y <= 0 && _direction.y < 0)
	{
		_direction.y *= -1;
		playSound();
	}

	// lose life bounce
	if (position.y > windowDimensions.y)
	{
		_sprite.setPosition(0, 300);
		_direction = { 1, 1 };
		_gameManager->loseLife();
		resetPitch();
	}

	// collision with paddle
	if (_sprite.getGlobalBounds().intersects(_gameManager->getPaddle()->getBounds()))
	{
		_direction.y *= -1; // Bounce vertically

		float paddlePositionProportion = (_sprite.getPosition().x - _gameManager->getPaddle()->getBounds().left) / _gameManager->getPaddle()->getBounds().width;
		_direction.x = paddlePositionProportion * 2.0f - 1.0f;

		// Adjust position to avoid getting stuck inside the paddle
		_sprite.setPosition(_sprite.getPosition().x, _gameManager->getPaddle()->getBounds().top - 2 * RADIUS);

		playSound();
	}

	// collision with bricks
	int collisionResponse = _gameManager->getBrickManager()->checkCollision(_sprite, _direction);
	if (!_isFireBall) {
		if (collisionResponse == 1)
		{
			_direction.x *= -1; // Bounce horizontally
			resetPitch();
		}
		else if (collisionResponse == 2)
		{
			_direction.y *= -1; // Bounce vertically
			resetPitch();
		}
	}
}

void Ball::render()
{
	for (sf::CircleShape& trail : _trails) {
		_window->draw(trail);
	}

	_window->draw(_sprite);
}

sf::Vector2f Ball::getPosition()
{
	return _sprite.getPosition();
}

void Ball::setVelocity(float coeff, float duration)
{
	_velocity = coeff * VELOCITY;
	_timeWithPowerupEffect = duration;
}

void Ball::setFireBall(float duration)
{
	if (duration)
	{
		_isFireBall = true;
		_timeWithPowerupEffect = duration;
		return;
	}
	_isFireBall = false;
	_timeWithPowerupEffect = 0.f;
}

void Ball::playSound()
{
	_ballBounceSound.setPitch(_ballBounceSound.getPitch() + PITCH_INCREASE_ON_BOUNCE);
	_ballBounceSound.play();
}

void Ball::resetPitch()
{
	_ballBounceSound.setPitch(BALL_BOUNCE_DEFAULT_PITCH);
}

void Ball::updateTrail(float dt)
{
	if constexpr (NUM_TRAILS == 0) return;

	_secondsSinceTrailSpawn += dt;
	if (_secondsSinceTrailSpawn < TRAIL_SPAWN_INTERVAL)  return;
	_secondsSinceTrailSpawn = 0;


	// move least recently used trail to ball pos, make it the same colour (with less alpha)
	_trails[_trailIndex].setPosition(_sprite.getPosition());
	sf::Color color = _sprite.getFillColor();
	color.r *= TRAIL_MODULATE;
	color.g *= TRAIL_MODULATE;
	color.b *= TRAIL_MODULATE;
	color.a = TRAIL_ALPHA;
	_trails[_trailIndex].setFillColor(color);
	_trailIndex = (_trailIndex + 1) % NUM_TRAILS;
}
