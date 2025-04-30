#include "Collidable.h"


bool Collidable::check(Collidable& other)
{
    std::optional<sf::FloatRect> intersection = m_rect.findIntersection(other.m_rect);
    return intersection == std::nullopt ? true : false;
}
  

bool Collidable::check(Collidable& other, sf::Vector2f& correction)
{
    
    if (this->check(other))
    {
        // Get the intersection rect
        std::optional<sf::FloatRect> inter = m_rect.findIntersection(other.m_rect);

        // Calculate overlap along the x and y axes
        float min = std::min(m_rect.position.x + m_rect.size.x, other.m_rect.position.x + other.m_rect.size.x);
        float max = std::max(m_rect.position.x, other.m_rect.position.x);
        float overlapX = min - max;

        min = std::min(m_rect.position.y + m_rect.size.y, other.m_rect.position.y + other.m_rect.size.y);
        max = std::max(m_rect.position.y, other.m_rect.position.y);
        float overlapY = min - max;
   
        // Check for potential edge cases
        if (overlapX == 0.0f && overlapY == 0.0f)
        {
            // Objects are exactly on top of each other, resolve collision along y-axis
            if (m_rect.position.y < other.m_rect.position.y)
                correction.y = -overlapY;
            else
                correction.y = overlapY;
        }
        else if (overlapX == 0.0f)
        {
            // Objects are colliding vertically, resolve collision along y-axis
            if (m_rect.position.y < other.m_rect.position.y)
                correction.y = -overlapY;
            else
                correction.y = overlapY;
        }
        else if (overlapY == 0.0f)
        {
            // Objects are colliding horizontally, resolve collision along x-axis
            if (m_rect.position.x < other.m_rect.position.x)
                correction.x = -overlapX;
            else
                correction.x = overlapX;
        }
        else
        {
            // Objects are colliding diagonally, resolve collision along the axis with smaller overlap
            if (overlapX < overlapY)
            {
                if (m_rect.position.x < other.m_rect.position.x)
                    correction.x = -overlapX;
                else
                    correction.x = overlapX;
            }
            else
            {
                if (m_rect.position.y < other.m_rect.position.y)
                    correction.y = -overlapY;
                else
                    correction.y = overlapY;
            }
        }
        return true;
    }
    return false;
}

const sf::FloatRect& Collidable::getBounds() const
{
    return m_rect;
}


sf::RectangleShape Collidable::getVisualBounds()
{
    sf::RectangleShape tmp({m_rect.size.x, m_rect.size.y});

    tmp.setFillColor(sf::Color::Transparent);
    tmp.setOutlineColor(sf::Color::Red);
    tmp.setOutlineThickness(1);

    return tmp;
}
