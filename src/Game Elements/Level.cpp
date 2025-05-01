#include "Level.h"

b2World Level::world { b2Vec2(0.0f, 9.8f) };

Level::Level()
{
}


Level::~Level()
{

}


sf::Vector2f Level::createFromImage(const sf::Image &levelImage)
{
    grid.clear();
    grid = std::vector(levelImage.getSize().x, std::vector<int>(levelImage.getSize().y, 0));
    sf::Vector2f playerPos;

    for(int x = 0; x < grid.size(); x++)
    {
        for(int y = 0; y < grid[x].size(); y++)
        {
            sf::Color pixel = levelImage.getPixel(sf::Vector2u(x, y));
            
            if(pixel == sf::Color::Black)
            {
                grid[x][y] = 1;

                // Create the body definition
                b2BodyDef def{};
                def.position.Set(BLOCK_SIZE * x, BLOCK_SIZE * y);

                // Create the body using pointers
                b2Body* body = world.CreateBody(&def);

                // Create the polygon (square) shape for visuals
                b2PolygonShape shape{};
                shape.SetAsBox(BLOCK_SIZE, BLOCK_SIZE);
                body->CreateFixture(&shape, 0.0f);
            }
            if(pixel == sf::Color::Blue)
            {
                grid[x][y] = 2;
                playerPos.x = BLOCK_SIZE * x; 
                playerPos.y = BLOCK_SIZE * y;
            }
        }
    }

    return playerPos;
}


void Level::draw(sf::RenderWindow &window) const
{
    int x = 0;
    for(const auto& column : grid)
    {
        int y = 0;
        for(const auto& cell : column)
        {
            if(cell == 1)
            {
                sf::Sprite block(Resources::get(textures::LevelTiles), 
                    sf::IntRect({32,0},{BLOCK_SIZE, BLOCK_SIZE}));

                block.setPosition(sf::Vector2f({(float)BLOCK_SIZE * x, (float)BLOCK_SIZE * y}));
                
                sf::RectangleShape s(block.getGlobalBounds().size);
                s.setPosition(block.getGlobalBounds().position);
                s.setOutlineThickness(1);
                s.setFillColor(sf::Color::Transparent);
                s.setOutlineColor(sf::Color::Blue);
                
                window.draw(block);
                window.draw(s);
            }
            if(cell == 0)
            {
                /*
                sf::RectangleShape a(sf::Vector2f({(float)BLOCK_SIZE, (float)BLOCK_SIZE}));
                a.setPosition(sf::Vector2f({(float)BLOCK_SIZE * x, (float)BLOCK_SIZE * y}));
                a.setOutlineThickness(1);
                a.setFillColor(sf::Color::Transparent);
                a.setOutlineColor(sf::Color::Green);
                window.draw(a);
                */
            }
            y++;
        }
        x++;
    }
}


void Level::init()
{

}


void Level::update(float dt)
{
    world.Step(dt, 6 , 2);
}
