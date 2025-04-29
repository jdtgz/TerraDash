#include "Resources.h"


std::map<textures::id, sf::Texture*> Resources::textureMap;


Resources::Resources()
{
	// Load all necessary PNG files
	load(textures::WORLD, "Textures/world1.png");
}


Resources::~Resources()
{
	for (auto tex : textureMap)
	{
		delete tex.second;
	}
}


void Resources::load(const textures::id& id, const std::string& filename)
{
	sf::Texture* txture = new sf::Texture();
	txture->loadFromFile(filename);
	textureMap.insert(std::make_pair(id, std::move(txture))); 
}


sf::Texture& Resources::get(const textures::id& id)
{
	std::map<textures::id, sf::Texture*>::iterator 
	found = textureMap.find(id);


	// Prevents loading of a non-existing texture in map
	if (found != textureMap.end())
		return *textureMap[found->first];
	else
	{
		sf::Texture emptyTex;
		return emptyTex;
	}
}