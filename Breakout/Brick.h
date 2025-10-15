#pragma once
#include <SFML/Graphics.hpp>

class Brick {
public:
    Brick(float x, float y, float width, float height);
    void render(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;

protected:
    sf::RectangleShape _shape;

private:
    bool _isDestroyed;
};