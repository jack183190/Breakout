#pragma once

#include <SFML/Graphics.hpp>

class ProgressBar
{
public:
	ProgressBar(sf::RenderWindow* window, sf::Vector2f position, sf::Vector2f size = { 200, 50 }, sf::Color foregroundColor = sf::Color::White, sf::Color backgroundColor = sf::Color::Black);

	void setMaximum(float max);
	void setProgress(float progress); 
	void render();

private:
	sf::RectangleShape _foreground;
	sf::RectangleShape _background;
	sf::RenderWindow* _window;
	float _maximum = 1;
};

