#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_circle_shape.h>
#include <box2d/b2_fixture.h>
#include "Animation.h"
#include "Resources.h"
#include "Level.h"


class Player : public ContactListener
{
    public:
        Player(sf::Vector2f p_pos, textures::ID txtID);
        ~Player();

        // Input processing 
        void keyPressed(sf::Keyboard::Scancode key);
        void keyReleased(sf::Keyboard::Scancode key);
        
        // Meant for game loop to step player into next state
        void update(const float& dt);
        
        // Draws player onto renderwindow for game       
        void draw(sf::RenderWindow& window) const;

        // Access var functions
        sf::Vector2f getPosition() const;
        int getHealth() const { return hp; }

        virtual void OnBeginContact() override;
        virtual void OnEndContact() override;
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
        textures::ID p_txt;
        sf::Sprite* p_visual;
        Animation p_animations[int(state::COUNT)];
        state curr_animation;

        // Handles all the movement aspects of the player
        enum class move
        {
            RIGHT = 0,
            LEFT, 
            UP,
            COUNT
        };
        bool heading[move::COUNT];
        bool key_movement[state::COUNT];\
        bool sprint;
        bool isGrounded;

        b2Body* p_body;
        
        // Player attributes
        int hp;
    };