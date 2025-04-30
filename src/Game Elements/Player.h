#pragma once

#include <SFML/Graphics.hpp>
#include "../Graphics/Animation.h"
#include "../Graphics/Resources.h"
#include "Collidable.h"


class Player : public Collidable
{
    public:
        Player();
        ~Player();

        void keyPressed(const sf::Keyboard::Key& key);

        void update(const float& dt);
        void draw(sf::RenderWindow& window) const;
    private:
        // Loads all approprite textures for the player and inits the idle 
        // animation by default and applies it to the sprite obj p_visual
        void initAnimations();

        // Handles all visual aspects of the player 
        enum class anim_index
        {
            IDLE = 0,
            WALK_RIGHT,
            WALK_LEFT,
            RUN_RIGHT,
            RUN_LEFT,
            JUMP_RIGHT,
            JUMP_LEFT,
            HURT,
            DEATH,
            COUNT
        };
        sf::Sprite* p_visual;
        textures::ID p_texture;
        Animation p_animations[int(anim_index::COUNT)];
        anim_index curr_animation;

        // Handles all the movement aspects of the player

};