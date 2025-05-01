#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_draw.h>
#include <vector>
#include "../Graphics/Resources.h"


class Debug;

class Level
{
    public:
        Level();
        ~Level();

        sf::Vector2f createFromImage(const sf::Image& levelImage);
        
        static void init();
        static void update(float dt);
        void draw(sf::RenderWindow& window) const;
        static void debugDraw(sf::RenderWindow& window);

        static b2World world;
        static Debug* world_debugger;
    private:
        std::vector<std::vector<int>> grid;
        const int BLOCK_SIZE = 32.0f; 

};