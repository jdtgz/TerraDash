#pragma once

#include <SFML/Graphics.hpp>
#include "Game Elements/Collidable.h"
#include "Game Elements/Level.h"
#include "Game Elements/Player.h"
#include "Graphics/Animation.h"
#include "Graphics/Resources.h"

 
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
        Resources gameTextures;
        Player player;
        Level level;
};

