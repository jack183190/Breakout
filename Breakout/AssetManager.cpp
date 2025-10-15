#include "AssetManager.h"
#include <iostream>

AssetManager::AssetManager()
{
	if (!ballBounceSound.loadFromFile("sfx/retro-coin-2-236685.mp3")) {
		std::cerr << "Failed to load ball bounce sound\n";
	}
}

const AssetManager& AssetManager::Singleton()
{
	static AssetManager inst;
	return inst;
}

