#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class AssetManager
{
private:
	AssetManager();

public:
	
	static const AssetManager& Singleton();

	sf::SoundBuffer ballBounceSound;
	sf::Texture eyeTexture;
};

