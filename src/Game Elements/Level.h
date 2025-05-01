#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <vector>
#include "../Graphics/Resources.h"


class Level
{
    public:
        Level();
        ~Level();

        sf::Vector2f createFromImage(const sf::Image& levelImage);
        void draw(sf::RenderWindow& window) const;

        static void init();
        static void update(float dt);

        static b2World world;
    private:
        std::vector<std::vector<int>> grid;
        const int BLOCK_SIZE = 32.0f; 

};