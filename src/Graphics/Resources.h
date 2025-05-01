#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <map>

namespace textures
{
	enum ID { Pink = 0, White, Blue, 
        LevelTiles, Back1, Back2, Back3, Back4, Back5 };
}

class Resources
{
    public:
        Resources(); 
        Resources(std::vector<std::string> files);
        ~Resources(); 

        static void load(const textures::ID&, const std::string&); 
        static sf::Texture& get(const textures::ID&); 
    private:
        static std::map<textures::ID, sf::Texture*> textureMap; 
};