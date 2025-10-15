#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

#include "CONSTANTS.h"
#include "PowerupManager.h"
#include "ProgressBar.h"

class LeaderboardManager;
class GameManager;

class UI
{
public:
	UI(sf::RenderWindow* window, int lives, GameManager* gameManager, LeaderboardManager& leaderboardManager);
	~UI();

	void updatePowerupText(std::pair<POWERUPS, float>);
	void lifeLost(int lives);
	void setScore(int score);
	void render();

private:
	GameManager* _gameManager;

	sf::RenderWindow* _window;
	sf::Font _font;
	sf::Text _scoreText;
	sf::Text _leaderboardText;
	sf::Text _powerupText;
	ProgressBar _powerupProgress;
	std::pair<POWERUPS, float> _currentPowerup;
	std::vector<sf::CircleShape> _lives;
	LeaderboardManager& _leaderboardManager;

	static constexpr float LIFE_RADIUS = 15.0f;
	static constexpr float LIFE_PADDING = 20.0f;
};

