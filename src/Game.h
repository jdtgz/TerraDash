#pragma once

#include <SFML/Graphics.hpp>
#include "Game Elements/Level.h"
#include "Graphics/Resources.h"
#include "Graphics/Animation.h"

 
class Game
{
    public:
        Game();
        ~Game();

        void run();

    private:
        void processEvents();
        void update(const sf::Time& dt);
        void render();

        // Window Elements
        sf::RenderWindow* window;
        sf::Time timePerFrame = sf::seconds(1.f / 60.f);

        // Game Elements
        sf::Sprite* player;
        Animation playerAnimations;
        Resources gameTextures;
        Level level;
};

