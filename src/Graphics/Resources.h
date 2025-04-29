#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <map>

namespace textures
{
	enum id { PLAYER = 0, WORLD };
}

class Resources
{
    public:
        Resources(); 
        ~Resources(); 

        static void load(const textures::id&, const std::string&); 
        static sf::Texture& get(const textures::id&); 
    private:
        static std::map<textures::id, sf::Texture*> textureMap; 
};