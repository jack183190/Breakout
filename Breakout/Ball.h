#pragma once
#include <SFML/Graphics.hpp>
#include "AssetManager.h"

class GameManager;  // forward declaration



class Ball {
public:
    Ball(sf::RenderWindow* window, float velocity, GameManager* gameManager);
    ~Ball();
    void update(float dt);
    void render();
    void setVelocity(float coeff, float duration);
    void setFireBall(float duration);

private:
    void playSound();
    void resetPitch();

private:
    sf::CircleShape _sprite;
    sf::Vector2f _direction;
    sf::RenderWindow* _window;
    float _velocity;
    bool _isAlive;
    bool _isFireBall;
    float _timeWithPowerupEffect;

    GameManager* _gameManager;  // Reference to the GameManager
    sf::Sound _ballBounceSound;

    static constexpr float RADIUS = 10.0f;      
    static constexpr float VELOCITY = 350.0f;   // for reference.
    static constexpr float PITCH_INCREASE_ON_BOUNCE = 0.2f;
    static constexpr float BALL_BOUNCE_DEFAULT_PITCH = 0.5f;
};

