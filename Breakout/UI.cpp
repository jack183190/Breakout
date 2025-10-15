#include <sstream>

#include "UI.h"
#include "GameManager.h"
#include <iomanip>

UI::UI(sf::RenderWindow* window, int lives, GameManager* gameManager)
	: _window(window), _gameManager(gameManager), _powerupProgress(window, sf::Vector2f{ 780, 10 })
{
	for (int i = lives; i > 0; --i)
	{
		sf::CircleShape newLife;
		newLife.setFillColor(sf::Color::Red);
		newLife.setOutlineColor(sf::Color::Cyan);
		newLife.setOutlineThickness(4.0f);
		newLife.setRadius(LIFE_RADIUS);
		newLife.setPosition((LIFE_RADIUS * 2 + LIFE_PADDING) * i, LIFE_PADDING);
		_lives.push_back(newLife);
	}
	_powerupText.setCharacterSize(30);
	_powerupText.setPosition(680, 10);
	_powerupText.setFillColor(sf::Color::Cyan);
	_font.loadFromFile("font/montS.ttf");
	_powerupText.setFont(_font);
	_currentPowerup = { none,0 };
}

UI::~UI()
{
}


void UI::updatePowerupText(std::pair<POWERUPS, float> powerup)
{
	std::ostringstream oss;

	// progress bar
	if (_currentPowerup.second < powerup.second) {
		// powerup changed
		_powerupProgress.setMaximum(powerup.second);
	}
	_currentPowerup = powerup;
	_powerupProgress.setProgress(powerup.second);

	switch (powerup.first)
	{
	case bigPaddle:
		_powerupText.setString("big");
		_powerupText.setFillColor(paddleEffectsColour);
		break;
	case smallPaddle:
		_powerupText.setString("small");
		_powerupText.setFillColor(paddleEffectsColour);
		break;
	case slowBall:
		_powerupText.setString("slow");
		_powerupText.setFillColor(ballEffectsColour);
		break;
	case fastBall:
		_powerupText.setString("fast");
		_powerupText.setFillColor(ballEffectsColour);
		break;
	case fireBall:
		_powerupText.setString("fire");
		_powerupText.setFillColor(extraBallEffectsColour);
		break;
	case none:
		_powerupText.setString("");

		break;
	}
}

void UI::lifeLost(int lives)
{
	_lives[_lives.size() - 1 - lives].setFillColor(sf::Color::Transparent);
}

void UI::render()
{
	_window->draw(_powerupText);
	if (_currentPowerup.first != none && _currentPowerup.second > 0)	_powerupProgress.render();
	for (sf::CircleShape life : _lives)
	{
		_window->draw(life);
	}
}