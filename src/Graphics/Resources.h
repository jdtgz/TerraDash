#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <map>

namespace textures
{
	enum id { Pink = 0, White, Blue };
}

class Resources
{
    public:
        Resources(); 
        Resources(std::vector<std::string> files);
        ~Resources(); 

        static void load(const textures::id&, const std::string&); 
        static sf::Texture& get(const textures::id&); 
    private:
        static std::map<textures::id, sf::Texture*> textureMap; 
};