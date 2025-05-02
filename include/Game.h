#pragma once

#include <SFML/Graphics.hpp>
#include "Level.h"
#include "Player.h"
#include "Animation.h"
#include "Resources.h"


class Game
{
    public:
        Game();
        ~Game();

        void run();
    private:
        void processEvents();
        void update(const float dt);
        void updateView();
        void render();

        // Window Elements
        sf::RenderWindow* window; 
        sf::View camera;
        const float ZOOM = 5.0f;

        // Game Elements
        Resources gameTextures;
        Player* player;
        Level level;
};

