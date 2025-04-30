#pragma once

#include <SFML/Graphics.hpp>


class Collidable
{
    public:
        bool check(Collidable& other);
        
        bool check(Collidable& other, sf::Vector2f& correction);
        
        const sf::FloatRect& getBounds() const;
       
        sf::RectangleShape getVisualBounds();

    protected:
        void updateRect(sf::FloatRect f);

    private:
        sf::FloatRect m_rect;
};