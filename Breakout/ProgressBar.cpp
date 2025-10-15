#include "ProgressBar.h"

ProgressBar::ProgressBar(sf::RenderWindow* window, sf::Vector2f position, sf::Vector2f size, sf::Color foregroundColor, sf::Color backgroundColor) : _window(window)
{
	_foreground.setPosition(position);
	_background.setPosition(position);
	_foreground.setSize(size);
	_background.setSize(size);	
	_foreground.setFillColor(foregroundColor);
	_background.setFillColor(backgroundColor);
}

void ProgressBar::setMaximum(float max)
{
	if (max == 0) max = FLT_EPSILON; // prevent division by 0
	_maximum = max;
}

void ProgressBar::setProgress(float progress)
{
	progress /= _maximum;

	sf::Vector2f size = _background.getSize();
	size.x *= progress;
	_foreground.setSize(size);
}


void ProgressBar::render() {
	_window->draw(_background);
	_window->draw(_foreground);
}