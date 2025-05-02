#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>
#include "../Graphics/Animation.h"
#include "../Graphics/Resources.h"
#include "Level.h"


class Player
{
    public:
        Player(sf::Vector2f p_pos);
        ~Player();

        void keyPressed(sf::Keyboard::Scancode key);
        void keyReleased(sf::Keyboard::Scancode key);
        void update(const float& dt);
        void draw(sf::RenderWindow& window) const;
    private:
        // Loads all approprite textures for the player and inits the idle 
        // animation by default and applies it to the sprite obj p_visual
        void initAnimations();

        // Used to track state of player and adjust visuals + moves
        enum class state
        {
            IDLE_RIGHT = 0,
            IDLE_LEFT,
            WALK_RIGHT,
            WALK_LEFT,
            RUN_RIGHT,
            RUN_LEFT,
            JUMP_RIGHT,
            JUMP_LEFT,
            HURT_RIGHT,
            HURT_LEFT,
            DEATH_RIGHT,
            DEATH_LEFT,
            COUNT
        };
        
        // Handles all visual aspects of the player 
        sf::Sprite* p_visual;
        Animation p_animations[int(state::COUNT)];
        state curr_animation;

        // Handles all the movement aspects of the player
        enum class move
        {
            RIGHT = 0,
            LEFT, 
            IN_AIR,
            COUNT
        };
        bool heading[move::COUNT];
        bool key_movement[state::COUNT];

        b2Body* body;
        
        // Player attributes
        int hp;
    };