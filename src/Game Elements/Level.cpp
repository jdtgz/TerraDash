#include "Level.h"

b2World Level::world { b2Vec2(0.0f, 10.0f) };

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
                def.position.Set(BLOCK_SIZE * x + BLOCK_SIZE / 2.0f, 
                    BLOCK_SIZE * y + BLOCK_SIZE / 2.0f);

                // Create the body using pointers
                b2Body* body = world.CreateBody(&def);

                // Create the polygon (square) shape for visuals
                b2PolygonShape shape{};
                shape.SetAsBox(BLOCK_SIZE / 2.0f, BLOCK_SIZE / 2.0f);
                body->CreateFixture(&shape, 0.0f);
            }
            if(pixel == sf::Color::Blue)
            {
                grid[x][y] = 2;
                playerPos.x = BLOCK_SIZE * x + BLOCK_SIZE / 2.0f;
                playerPos.y = BLOCK_SIZE * y + BLOCK_SIZE / 2.0f;
            }
        }
    }

    return playerPos;
}


void Level::draw(sf::RenderWindow &window) const
{
    sf::IntRect tmp({32,0},{BLOCK_SIZE, BLOCK_SIZE});

    int x = 0;
    for(const auto& column : grid)
    {
        int y = 0;
        for(const auto& cell : column)
        {
            if(cell == 1)
            {
                sf::Vector2f pos({BLOCK_SIZE * x + BLOCK_SIZE / 2.0f, BLOCK_SIZE * y + BLOCK_SIZE / 2.0f});
                
                sf::Sprite block(Resources::get(textures::LevelTiles), tmp);
                block.setPosition(pos);

                /*
                if(x < 10 && y < 10)
                {
                    std::cout << "grid[" << x << "][" << y << "]:\n";
                    std::cout << "Pos: [ " << pos.x << ", " << pos.y << " ]\n";
                    std::cout << "Origin ( " << block.getOrigin().x  << ", " << block.getOrigin().y << " )\n" << std::endl;
                }
                */
                
                window.draw(block);
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
    world.Step(dt, 8 , 3);
}
