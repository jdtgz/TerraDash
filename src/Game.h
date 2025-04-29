/*
 * Purpose: 
 */

 #pragma once
 #include <SFML/Graphics.hpp>
 #include "Game Elements/Level.h"
 
 
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

        sf::RenderWindow* window;
        sf::Time timePerFrame = sf::seconds(1.f / 60.f);

        sf::RectangleShape runner;
        Level level;
};

