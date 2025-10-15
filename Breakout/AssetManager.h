#pragma once

#include <SFML/Audio.hpp>

class AssetManager
{
private:
	AssetManager();

public:
	
	static const AssetManager& Singleton();

	sf::SoundBuffer ballBounceSound;
	
};

