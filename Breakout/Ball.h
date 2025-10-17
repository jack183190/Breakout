#pragma once
#include <SFML/Graphics.hpp>
#include "AssetManager.h"
#include <array>

class GameManager;  // forward declaration



class Ball {
public:
	Ball(sf::RenderWindow* window, float velocity, GameManager* gameManager);
	~Ball();
	void update(float dt);
	void render();
	void setVelocity(float coeff, float duration);
	void setFireBall(float duration);
	sf::Vector2f getPosition();

private:
	void playSound();
	void resetPitch();
	void updateTrail(float dt);

private:
	static constexpr float RADIUS = 10.0f;
	static constexpr float VELOCITY = 350.0f;   // for reference.
	static constexpr float PITCH_INCREASE_ON_BOUNCE = 0.2f;
	static constexpr float BALL_BOUNCE_DEFAULT_PITCH = 0.5f;
	static constexpr float TRAIL_MODULATE = 0.8f; // multiplied with each component of RGB
	static constexpr unsigned char TRAIL_ALPHA = 60;
	static constexpr float TRAIL_SPAWN_INTERVAL = 0.02f;
	static constexpr size_t NUM_TRAILS = 7;

	sf::CircleShape _sprite;
	std::array<sf::CircleShape, NUM_TRAILS> _trails;
	size_t _trailIndex = 0;
	float _secondsSinceTrailSpawn = 0;
	sf::Vector2f _direction;
	sf::RenderWindow* _window;
	float _velocity;
	bool _isAlive;
	bool _isFireBall;
	float _timeWithPowerupEffect;

	GameManager* _gameManager;  // Reference to the GameManager
	sf::Sound _ballBounceSound;
};

