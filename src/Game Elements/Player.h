#pragma once

#include <SFML/Graphics.hpp>
#include "../Graphics/Animation.h"
#include "../Graphics/Resources.h"


class Player
{
    public:
        Player();
        ~Player();

        void keyPressed(sf::Keyboard::Scancode key);
        void keyReleased(sf::Keyboard::Scancode key);
        void update(const float& dt);
        void draw(sf::RenderWindow& window) const;

        void setPos(sf::Vector2f pos);
        sf::Vector2f getPos() { return p_visual->getPosition(); }
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
        textures::ID p_texture;
        Animation p_animations[int(state::COUNT)];
        state curr_animation;

        // Handles all the movement aspects of the player
        bool key_movement[state::COUNT];
        sf::Vector2f vel; 

        // Game attributes
        int hp;
    };