#pragma once

#include <SFML/Graphics.hpp>
#include "Level.h"
#include "Player.h"
#include "Animation.h"
#include "Resources.h"


class Game
{
    public:
        Game(textures::ID p_id);
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

        // Game Elements
        Player* player;
        Level level;
};

