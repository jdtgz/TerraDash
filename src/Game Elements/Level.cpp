#include "Level.h"

b2World Level::world { b2Vec2(0.0f, 9.8f) };
Debug* Level::world_debugger{};


class Debug : public b2Draw
{
    public:
        Debug(sf::RenderTarget& target) : target(target) 
        {
        }

        virtual void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
        {
            sf::ConvexShape shape(vertexCount);
            for(int i = 0; i < vertexCount; i++)
            {
                shape.setPoint(i, sf::Vector2f({vertices[i].x, vertices[i].y}));
            }
            shape.setFillColor(sf::Color::Transparent);
            shape.setOutlineThickness(0.1f);
            shape.setOutlineColor(sf::Color(color.r * 255, color.g * 255, color.b * 255, color.a * 255));
            target.draw(shape);
        }

        /// Draw a solid closed polygon provided in CCW order.
        virtual void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
        {
            sf::ConvexShape shape(vertexCount);
            for(int i = 0; i < vertexCount; i++)
            {
                shape.setPoint(i, sf::Vector2f({vertices[i].x, vertices[i].y}));
            }
            shape.setFillColor(sf::Color(color.r * 255, color.g * 255, color.b * 255, color.a * 255));
            target.draw(shape);
        }

        /// Draw a circle.
        virtual void DrawCircle(const b2Vec2& center, float radius, const b2Color& color)
        {
            sf::CircleShape circle(radius);
            circle.setPosition({center.x, center.y});
            circle.setOrigin({radius / 2.0f, radius / 2.0f});
            circle.setFillColor(sf::Color::Transparent);
            circle.setOutlineThickness(0.02f);
            circle.setOutlineColor(sf::Color(color.r * 255, color.g * 255, color.b * 255, color.a * 255));
            target.draw(circle);
        }

        /// Draw a solid circle.
        virtual void DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color)
        {
            sf::CircleShape circle(radius);
            circle.setPosition({center.x, center.y});
            circle.setOrigin({radius / 2.0f, radius / 2.0f});
            circle.setFillColor(sf::Color(color.r * 255, color.g * 255, color.b * 255, color.a * 80));
            target.draw(circle);

            b2Vec2 p = center + (radius * axis);
            DrawSegment(center, p, color);
        }

        /// Draw a line segment.
        virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
        {
            sf::VertexArray va(sf::PrimitiveType::Lines, 2);
            sf::Color sfColor(sf::Color(color.r * 255, color.g * 255, color.b * 255, color.a * 80));

            va[0].position = sf::Vector2f({p1.x, p1.y});
            va[0].color = sfColor;

            va[1].position = sf::Vector2f({p2.x, p2.y});
            va[1].color = sfColor;

            target.draw(va);
        }

        /// Draw a transform. Choose your own length scale.
        /// @param xf a transform.
        virtual void DrawTransform(const b2Transform& xf)
        {
            b2Vec2 p = xf.p;
            b2Vec2 px = p + (xf.q.GetXAxis());
            b2Vec2 py = p + (xf.q.GetYAxis());
            
            DrawSegment(p, px, b2Color(1.0f, 0.0f, 0.0f));
            DrawSegment(p, py, b2Color(0.0f, 1.0f, 0.0f));
        }

        /// Draw a point.
        virtual void DrawPoint(const b2Vec2& p, float size, const b2Color& color)
        {
            sf::CircleShape circle(size);
            circle.setPosition({p.x, p.y});
            circle.setOrigin({size / 2.0f, size / 2.0f});
            circle.setFillColor(sf::Color(color.r * 255, color.g * 255, color.b * 255, color.a * 255));
            target.draw(circle);
        }
    private:
        sf::RenderTarget& target;  
};


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


void Level::init()
{
    
}


void Level::update(float dt)
{
    world.Step(dt, 6 , 2);
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
                /*
                sf::RectangleShape s(block.getGlobalBounds().size);
                s.setPosition(block.getGlobalBounds().position);
                s.setOutlineThickness(1);
                s.setFillColor(sf::Color::Transparent);
                s.setOutlineColor(sf::Color::Blue);
                */
                window.draw(block);
                //window.draw(s);
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


void Level::debugDraw(sf::RenderWindow& window)
{
    if(!world_debugger)
    {
        sf::RenderTarget& tmp(window);
        world_debugger = new Debug(tmp);
        world_debugger->SetFlags(b2Draw::e_shapeBit);
        world.SetDebugDraw(world_debugger);
    }

    world.DebugDraw();
}