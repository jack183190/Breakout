#pragma once

#include <SFML/Graphics.hpp>
#include "CONSTANTS.h"

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

private:
    void initEye(sf::RectangleShape& rect);

private:
    static constexpr float EYE_OFFSET_FROM_EDGE = 8; // px
    static constexpr float BLINK_SHOW_TIME = 4.0f;
    static constexpr float BLINK_HIDE_TIME = 0.35f;

    sf::RenderWindow* _window;
    sf::RectangleShape _sprite;
    sf::RectangleShape _eye1;
    sf::RectangleShape _eye2;
    float _width = PADDLE_WIDTH;
    bool _isAlive;
    float _timeInNewSize = 0.0f;
    float _eyeTimer = 0;
};
