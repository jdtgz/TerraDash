#include "Level.h"


Level::Level()
{
}


Level::~Level()
{

}


void Level::generate()
{

}


void Level::createFromImage(const sf::Image &levelImage)
{
    world.clear();
    world = std::vector(levelImage.getSize().x, std::vector<int>(levelImage.getSize().y, 0));

    for(int x = 0; x < world.size(); x++)
    {
        for(int y = 0; y < world[x].size(); y++)
        {
            sf::Color pixel = levelImage.getPixel(sf::Vector2u(x, y));
            
            if(pixel == sf::Color::Black)
                world[x][y] = 1;
        }
    }

}


void Level::draw(sf::RenderWindow &window) const
{
    sf::IntRect tmp({32,0},{BLOCK_SIZE, BLOCK_SIZE});
    int x = 0;
    for(const auto& column : world)
    {
        int y = 0;
        for(const auto& cell : column)
        {
            if(cell)
            {
                sf::Sprite block(Resources::get(textures::LevelTiles));


                sf::Vector2f pos({BLOCK_SIZE * x + BLOCK_SIZE / 2.0f, BLOCK_SIZE * y + BLOCK_SIZE / 2.0f});

                block.setTextureRect(tmp);
                block.setPosition(pos);
                
                window.draw(block);
            }
            y++;
        }
        x++;
    }
}
