/*
 * Purpose: 
 */

 #pragma once
 #include "SFML/Graphics.hpp"
 
 
 class Game
 {
     public:
         Game();
         ~Game();
 
         void run();
         
     private:
         void processEvents();
         void update(const sf::Time&);
         void render();
 
         sf::RenderWindow* window;
 
         sf::Time timePerFrame = sf::seconds(1.f / 60.f);
         // Level Obj 
         // Player Obj
         sf::RectangleShape* player;
         // Start Menu Obj 
 };
 
 