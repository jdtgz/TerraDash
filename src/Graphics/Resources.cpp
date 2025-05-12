#include "Resources.h"


std::map<textures::ID, sf::Texture*> Resources::textureMap;


Resources::Resources()
{
	// Load all the player images
	load(textures::ID::Pink, "Textures/Players/Pink_Player.png");
	load(textures::ID::White, "Textures/Players/White_Player.png");
	load(textures::ID::Blue, "Textures/Players/Blue_Player.png");

	// Load all the world building images
	load(textures::ID::LevelTiles, "Textures/Worlds/LevelTiles.png");
	load(textures::ID::SpikeTiles, "Textures/Worlds/SpikeTiles.png");
	load(textures::ID::WaterTiles, "Textures/Worlds/WaterTiles.png");
	load(textures::ID::Back1, "Textures/Worlds/Background1.png");
	load(textures::ID::Back2, "Textures/Worlds/Background2.png");
	load(textures::ID::Back3, "Textures/Worlds/Background3.png");
	load(textures::ID::Back4, "Textures/Worlds/Background4.png");
	load(textures::ID::Back5, "Textures/Worlds/Background5.png");
	load(textures::ID::StartMenu, "Textures/Start Menu.png");
	load(textures::ID::PlayerSelect, "Textures/Player Selection Menu.png");
}


Resources::~Resources()
{
	for (auto tex : textureMap)
	{
		delete tex.second;
	}
}


void Resources::load(const textures::ID& id, const std::string& filename)
{
	sf::Texture* txture = new sf::Texture();
	txture->loadFromFile(filename);
	textureMap.insert(std::make_pair(id, std::move(txture))); 
}


sf::Texture& Resources::get(const textures::ID& id)
{
	auto found = textureMap.find(id);

	if (found != textureMap.end())
		return *found->second;
	else
	{
		static sf::Texture fallback;
		std::cerr << "Missing texture for ID " << int(id) << std::endl;
		return fallback;
	}
}