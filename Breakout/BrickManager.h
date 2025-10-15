#pragma once
#include <vector>
#include "Brick.h"
#include <SFML/Graphics.hpp>
#include "BrickParticle.h"
#include <array>

class GameManager;

class BrickManager {
public:
    BrickManager(sf::RenderWindow* window, GameManager* gameManager);
    void createBricks(int rows, int cols, float brickWidth, float brickHeight, float spacing);
    void render();
    int checkCollision(sf::CircleShape& ball, sf::Vector2f& direction);
    void update(float dt);

private:
    void spawnParticle(sf::Vector2f pos, sf::Vector2f ballDirection);

private:
    static constexpr float TOP_PADDING = 100.0f;
    static constexpr size_t MAX_PARTICLES = 15;
    static constexpr float PARTICLE_ANGULAR_VELOCITY = 60;

    std::vector<Brick> _bricks;
    sf::RenderWindow* _window;
    std::array<BrickParticle, MAX_PARTICLES> _particles;

    GameManager* _gameManager;
};
