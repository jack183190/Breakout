#pragma once

#include <SFML/Graphics.hpp>
#include "CONSTANTS.h"

class Ball;
class Paddle
{
public:
    Paddle(sf::RenderWindow* window);
    ~Paddle();

    void moveLeft(float dt);
    void moveRight(float dt);
    void update(float dt);
    void render();
    sf::FloatRect getBounds() const;
    void setWidth(float coeff, float duration);
    void setBall(Ball* ball);

private:
    void initEye(sf::RectangleShape& rect);

private:
    static constexpr float EYE_OFFSET_FROM_EDGE = 8; // px
    static constexpr float BLINK_SHOW_TIME = 4.0f;
    static constexpr float BLINK_HIDE_TIME = 0.35f;
    static constexpr float SADDEST_MOUTH_DISTANCE = 600; // how many pixels away should the ball be for the saddest mouth variant to be shown
    static constexpr unsigned int NUM_MOUTHS = 3;
    static_assert(NUM_MOUTHS >= 1);

    sf::RenderWindow* _window;
    sf::RectangleShape _sprite;
    sf::RectangleShape _eye1;
    sf::RectangleShape _eye2;
    sf::RectangleShape _mouth;
    float _width = PADDLE_WIDTH;
    bool _isAlive;
    float _timeInNewSize = 0.0f;
    float _eyeTimer = 0;
    Ball* _ball = nullptr;
};
