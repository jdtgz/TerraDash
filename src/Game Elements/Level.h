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
        void createFromImage(const sf::Image& levelImage);
        void draw(sf::RenderWindow& window) const;
    private:
        std::vector<std::vector<int>> world;
};