#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "../Graphics/Resources.h"


class Level
{
    public:
        Level();
        ~Level();

        void generate();
        sf::Vector2f createFromImage(const sf::Image& levelImage);
        void draw(sf::RenderWindow& window) const;
    private:
        std::vector<std::vector<int>> world;
        const int BLOCK_SIZE = 32; 
};