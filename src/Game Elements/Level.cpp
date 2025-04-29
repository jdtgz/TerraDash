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
    int x = 0;
    for(const auto& column : world)
    {
        int y = 0;
        for(const auto& cell : column)
        {
            if(cell)
            {
                sf::RectangleShape block;
                block.setFillColor(sf::Color::Green);
                block.setOutlineThickness(1);
                block.setOutlineColor(sf::Color::Blue);
                block.setSize({20.f,20.f});
                block.setPosition({20.f * x + 20.f / 2.0f, 20.f * y + 20.f / 2.0f});
                
                window.draw(block);
            }
            y++;
        }
        x++;
    }
}
