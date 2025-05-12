#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_world_callbacks.h>
#include <box2d/b2_contact.h>
#include <box2d/b2_draw.h>
#include <vector>
#include "Resources.h"


class Debug;


class ContactListener;


class ContactListener
{
    public:
        virtual void OnBeginContact() = 0;
        virtual void OnEndContact() = 0;
};


class Level
{
    public:
        Level();
        ~Level();

        sf::Vector2f createFromImage(const sf::Image& levelImage);
        
        static void init();
        void update(float dt, sf::Vector2f pos);
        void draw(sf::RenderWindow& window) const;
        static void debugDraw(sf::RenderWindow& window);

        static b2World world;
        static Debug* world_debugger;
        bool playerReachedGoal(const sf::Vector2f& playerPos) const;
    private:
        std::vector<std::vector<int>> grid;
        std::vector<b2Body*> tiles;
        const int BLOCK_SIZE = 32.0f; 
        sf::Vector2f goalPos;
};