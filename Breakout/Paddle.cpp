#include "Paddle.h"
#include <iostream>
#include "AssetManager.h"
#include "Ball.h"
#include "Utils.h"

Paddle::Paddle(sf::RenderWindow* window)
	: _window(window), _width(PADDLE_WIDTH), _timeInNewSize(0.0f), _isAlive(true)
{
	_sprite.setFillColor(sf::Color::Cyan);
	_sprite.setPosition((window->getSize().x - _width) / 2.0f, window->getSize().y - 50.0f);
	_sprite.setSize(sf::Vector2f(_width, PADDLE_HEIGHT));

	initEye(_eye1);
	initEye(_eye2);

	_mouth.setTexture(&AssetManager::Singleton().mouthTexture);
	sf::Vector2u mouthTexSize = AssetManager::Singleton().mouthTexture.getSize();
	_mouth.setSize({ static_cast<float>(mouthTexSize.x),	static_cast<float>(mouthTexSize.y) / NUM_MOUTHS });
}

Paddle::~Paddle()
{
}

void Paddle::moveLeft(float dt)
{
	float position = _sprite.getPosition().x;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && position > 0)
	{
		_sprite.move(sf::Vector2f(-dt * PADDLE_SPEED, 0));
	}
}

void Paddle::moveRight(float dt)
{
	float position = _sprite.getPosition().x;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && position < _window->getSize().x - _width)
	{
		_sprite.move(sf::Vector2f(dt * PADDLE_SPEED, 0));
	}
}

void Paddle::update(float dt)
{
	if (_timeInNewSize > 0)
	{
		_timeInNewSize -= dt;
	}
	else
	{
		setWidth(1.0f, 0.0f); // Reset to default width after duration
	}

	_eyeTimer += dt;
	if (_eyeTimer >= BLINK_SHOW_TIME + BLINK_HIDE_TIME) {
		_eyeTimer = 0;
	}

	sf::Vector2u mouthTexSize = AssetManager::Singleton().mouthTexture.getSize();
	const sf::Vector2f spriteCenter = _sprite.getPosition() + _sprite.getSize() / 2.0f;

	if (_ball) {
		sf::Vector2f toBall = spriteCenter - _ball->getPosition();
		float distanceToBall = sqrt(toBall.x * toBall.x + toBall.y * toBall.y);
		int mouthIndex = std::clamp(Utils::remap(distanceToBall, 0.0f, SADDEST_MOUTH_DISTANCE, 0.0f, NUM_MOUTHS - 1.0f), 0.0f, static_cast<float>(NUM_MOUTHS - 1.0f));
		_mouth.setTextureRect({
			0,
			static_cast<int>(mouthTexSize.y / NUM_MOUTHS * mouthIndex),
			static_cast<int>(mouthTexSize.x),
			static_cast<int>(mouthTexSize.y / NUM_MOUTHS)
		});

	}

	_mouth.setPosition({ spriteCenter.x - _mouth.getSize().x / 2, _sprite.getPosition().y });

	_eye1.setPosition({ _sprite.getPosition().x + EYE_OFFSET_FROM_EDGE, _sprite.getPosition().y });
	_eye2.setPosition({ _sprite.getPosition().x - EYE_OFFSET_FROM_EDGE - _eye2.getSize().x + _sprite.getSize().x, _sprite.getPosition().y });
}

void Paddle::render()
{
	_window->draw(_sprite);
	_window->draw(_mouth);

	if (_eyeTimer <= BLINK_SHOW_TIME) {
		_window->draw(_eye1);
		_window->draw(_eye2);
	}
}

sf::FloatRect Paddle::getBounds() const
{
	return _sprite.getGlobalBounds();
}

// update width by SF of coeff. 
// ensure centre remains consistent.
void Paddle::setWidth(float coeff, float duration)
{
	_width = coeff * PADDLE_WIDTH;
	_sprite.setSize(sf::Vector2f(_width, _sprite.getSize().y));
	_timeInNewSize = duration;
	float newX = _sprite.getPosition().x + (_width - PADDLE_WIDTH) / 2;
	_sprite.setPosition(newX, _sprite.getPosition().y);
}

void Paddle::setBall(Ball* ball)
{
	_ball = ball;
}

void Paddle::initEye(sf::RectangleShape& rect)
{
	rect.setSize({ 20,20 });
	rect.setTexture(&AssetManager::Singleton().eyeTexture);
}
