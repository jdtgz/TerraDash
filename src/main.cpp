/*
 * Authors: Daniel Toro Gil, Ben Bryant, Riley Carter
 */

//#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"


int runStartMenu();

bool playerSelection(sf::Sprite& s, sf::Sprite* sprites[], Animation anims[]);


int main()
{
    Resources gameTextures;
    int choice = runStartMenu();
    
    Game* game = new Game(textures::ID(choice));
    game->run();
    delete game;
}


int runStartMenu()
{
    sf::RenderWindow startMenu(sf::VideoMode({ 1024, 1024 }), "TerraDashMenu");

    // Init the background for the start menu
    sf::Sprite m_background(Resources::get(textures::StartMenu));
    m_background.setTextureRect(sf::IntRect({ 0, 0 }, { 1024, 1024 }));
    m_background.setOrigin({ 512.0f, 512.0f });
    m_background.setPosition({ 512.0f, 512.0f });

    // Init the player idle animations for selection
    sf::Sprite* c_sprites[3];
    Animation c_anims[3];
    bool playerSelectionActive = false;

    int id = 0;

    sf::Clock clock;
    while(startMenu.isOpen())
    {
        float dt = clock.restart().asSeconds();

        while(const std::optional event = startMenu.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                startMenu.close();

            else if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                sf::Vector2f cursor(mousePressed->position.x, mousePressed->position.y);
                
                if(!playerSelectionActive)
                {
                    sf::FloatRect startBox({318.0f , 695.0f}, {388.0f, 157.0f});
                    
                    if(startBox.contains(cursor))
                        playerSelectionActive = playerSelection(m_background, c_sprites, c_anims);
                }
                else
                {
                    sf::FloatRect pinkBox(c_sprites[textures::Pink]->getGlobalBounds());
                    sf::FloatRect whiteBox(c_sprites[textures::White]->getGlobalBounds());
                    sf::FloatRect blueBox(c_sprites[textures::Blue]->getGlobalBounds());
                    
                    if(pinkBox.contains(cursor))
                    {
                        id = int(textures::Pink);
                        startMenu.close();
                    }
                    else if(whiteBox.contains(cursor))
                    {
                        id = int(textures::White);
                        startMenu.close();
                    }
                    else if(blueBox.contains(cursor))
                    {
                        id = int(textures::Blue);
                        startMenu.close();
                    }
                }
            }
        }


        if(playerSelectionActive)
        {
            for(int i = 0; i < 3; i++)
            {
                c_sprites[i]->setPosition({512, 350.f + (170 * i)});
                c_anims[i].update(dt);
                c_anims[i].applyToSprite(*c_sprites[i], 4, 5);
            }
        }

        startMenu.clear();

        startMenu.draw(m_background);

        // draw players
        if(playerSelectionActive)
        {
            for(int i = 0; i < 3; i++)
                startMenu.draw(*c_sprites[i]);
        }

        startMenu.display();
    }
    
    for(int i = 0; i < 3; i++)
        delete c_sprites[i];

    return id;
}


bool playerSelection(sf::Sprite& s, sf::Sprite* sprites[], Animation anims[])
{
    s.setTexture(Resources::get(textures::PlayerSelect));
    s.setTextureRect(sf::IntRect({ 0, 0 }, { 1024, 1024 }));
    s.setOrigin({ 512.0f, 512.0f });
    s.setPosition({ 512.0f, 512.0f });

    // Init the player animations and sprites
    sf::Vector2i size({32, 32});
    sf::Vector2i position({0, 32});

    sf::Texture* t = &Resources::get(textures::Pink);
    sprites[textures::Pink] = new sf::Sprite(*t);
    anims[textures::Pink].setUp(*t, position, size, 4);

    t = &Resources::get(textures::White);
    sprites[textures::White] = new sf::Sprite(*t);
    anims[textures::White].setUp(*t ,position, size, 4);

    t = &Resources::get(textures::Blue);
    sprites[textures::Blue] = new sf::Sprite(*t);
    anims[textures::Blue].setUp(*t, position, size, 4); 

    for(int i = 0; i < 3; i++)
    {
        anims[i].setFrame(0);
        anims[i].applyToSprite(*sprites[i], 4, 5);
    }

    return true;
}