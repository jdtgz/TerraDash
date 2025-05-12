#include "Level.h"

b2World Level::world { b2Vec2(0.0f, 9.8f) };
Debug* Level::world_debugger{};

constexpr float SCALE = 32.f; 

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
                shape.setPoint(i, sf::Vector2f({vertices[i].x * SCALE, vertices[i].y * SCALE}));
            
            shape.setOutlineThickness(0.5f);
            shape.setFillColor(sf::Color::Transparent);
            shape.setOutlineColor(sf::Color(color.r * 255, color.g * 255, color.b * 255, color.a * 255));
            
            target.draw(shape);
        }

        
        virtual void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
        {
            sf::ConvexShape shape(vertexCount);
            for(int i = 0; i < vertexCount; i++)
                shape.setPoint(i, sf::Vector2f({vertices[i].x * SCALE, vertices[i].y * SCALE}));
            
            shape.setFillColor(sf::Color(color.r * 255, color.g * 255, color.b * 255, color.a * 120));
            
            target.draw(shape);
        }


        virtual void DrawCircle(const b2Vec2& center, float radius, const b2Color& color)
        {
            sf::CircleShape circle(radius * SCALE);
            circle.setPosition({center.x * SCALE, center.y * SCALE});
            circle.setOrigin({radius * SCALE, radius * SCALE});

            circle.setOutlineThickness(0.5f);
            circle.setFillColor(sf::Color::Transparent);
            circle.setOutlineColor(sf::Color(color.r * 255, color.g * 255, color.b * 255, color.a * 255));

            target.draw(circle);
        }


        virtual void DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color)
        {
            sf::CircleShape circle(radius * SCALE);
            circle.setPosition({center.x * SCALE, center.y * SCALE});
            circle.setOrigin({radius * SCALE, radius * SCALE});

            circle.setFillColor(sf::Color(color.r * 255, color.g * 255, color.b * 255, color.a * 120));
            
            target.draw(circle);

            b2Vec2 p = center + radius * axis;
            DrawSegment(center, p, color);
        }


        virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
        {
            sf::VertexArray va(sf::PrimitiveType::Lines, 2);
            sf::Color sfColor(sf::Color(color.r * 255, color.g * 255, color.b * 255, color.a * 255));

            va[0].position = sf::Vector2f({p1.x * SCALE, p1.y * SCALE});
            va[0].color = sfColor;

            va[1].position = sf::Vector2f({p2.x * SCALE, p2.y * SCALE});
            va[1].color = sfColor;

            target.draw(va);
        }


        virtual void DrawTransform(const b2Transform& xf)
        {
            b2Vec2 p = xf.p;
            b2Vec2 px = p + (0.5f * xf.q.GetXAxis());
            b2Vec2 py = p + (0.5f * xf.q.GetYAxis());
            
            DrawSegment(p, px, b2Color(1.0f, 0.0f, 0.0f));
            DrawSegment(p, py, b2Color(0.0f, 1.0f, 0.0f));
        }


        virtual void DrawPoint(const b2Vec2& p, float size, const b2Color& color)
        {
            sf::CircleShape circle(size);
            circle.setPosition({p.x * SCALE, p.y * SCALE});
            circle.setOrigin({size * SCALE, size * SCALE});
            circle.setFillColor(sf::Color(color.r * 255, color.g * 255, color.b * 255, color.a * 255));

            target.draw(circle);
        }
    private:
        sf::RenderTarget& target;  
};


class GlobalContactListener : public b2ContactListener
{
    public:
        virtual void BeginContact(b2Contact* contact) override
        {
            ContactListener* listener = (ContactListener*)contact->GetFixtureA()->GetUserData().pointer;

            if(listener)
                listener->OnBeginContact();

            listener = (ContactListener*)contact->GetFixtureB()->GetUserData().pointer;

            if(listener)
                listener->OnBeginContact();
        }

        virtual void EndContact(b2Contact* contact) override
        {
             ContactListener* listener = (ContactListener*)contact->GetFixtureA()->GetUserData().pointer;

            if(listener)
                listener->OnEndContact();

            listener = (ContactListener*)contact->GetFixtureB()->GetUserData().pointer;

            if(listener)
                listener->OnEndContact();
        }
};


Level::Level()
{
    background = new sf::Sprite(Resources::get(textures::Back1), 
                            sf::IntRect({0, 0}, {1920, 1080}));
    background->setOrigin({860.0f, 540.0f});
}


Level::~Level()
{
    delete world_debugger;
    delete background;
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
            
            if(pixel.a < 255)
            {
                switch(pixel.a - 100)
                {
                    case int(TileType::SINGLE):
                        grid[x][y] = int(TileType::SINGLE);
                        break;
                    
                    // all top blocks
                    case int(TileType::TOP1):
                        grid[x][y] = int(TileType::TOP1);
                        break;
                    case int(TileType::TOP2):
                        grid[x][y] = int(TileType::TOP2);
                        break;
                    case int(TileType::TOP3):
                        grid[x][y] = int(TileType::TOP3);
                        break;
                    case int(TileType::TOP4):
                        grid[x][y] = int(TileType::TOP4);
                        break;
                    case int(TileType::TOP5):
                        grid[x][y] = int(TileType::TOP5);
                        break;
                    case int(TileType::TOP6):
                        grid[x][y] = int(TileType::TOP6);
                        break;
                    case int(TileType::TOP7):
                        grid[x][y] = int(TileType::TOP7);
                        break;
                    
                    // all middle blocks
                    case int(TileType::MID1):
                        grid[x][y] = int(TileType::MID1);
                        break;
                    case int(TileType::MID2):
                        grid[x][y] = int(TileType::MID2);
                        break;
                    case int(TileType::MID3):
                        grid[x][y] = int(TileType::MID3);
                        break;
                    case int(TileType::MID4):
                        grid[x][y] = int(TileType::MID4);
                        break;
                    
                    // all bottom blocks
                    case int(TileType::BOTTOM1):
                        grid[x][y] = int(TileType::BOTTOM1);
                        break;
                    case int(TileType::BOTTOM2):
                        grid[x][y] = int(TileType::BOTTOM2);
                        break;
                    case int(TileType::BOTTOM3):
                        grid[x][y] = int(TileType::BOTTOM3);
                        break;
                    case int(TileType::BOTTOM4):
                        grid[x][y] = int(TileType::BOTTOM4);
                        break;
                }
                createBody(x,y);
            }
            else
            {
                if (pixel == sf::Color::Blue)
                {
                    grid[x][y] = 19;
                    playerPos.x = BLOCK_SIZE * x + BLOCK_SIZE / 2.0f; 
                    playerPos.y = BLOCK_SIZE * y + BLOCK_SIZE / 2.0f;
                }
                if (pixel == sf::Color::Green)
                {
                    grid[x][y] = 17;
                    createBody(x, y);
                }
                if (pixel == sf::Color::Magenta)
                {
                    grid[x][y] = 18;
                    createBody(x, y);
                }
            }
        }
    }

    return playerPos;
}


void Level::update(float dt, sf::Vector2f pos)
{
    world.Step(dt, 8, 3);
    world.SetContactListener(new GlobalContactListener());
    background->setPosition(pos);
}


void Level::draw(sf::RenderWindow &window) const
{
    window.draw(*background);

    int x = 0;
    int tile = 0;
    for(const auto& column : grid)
    {
        int y = 0;
        for(const auto& cell : column)
        {

            if(cell < 17 && cell > 0)
            {
                // Select correct position for tile box
                sf::Vector2i  rectPos({0, 0});
                switch(cell)
                {
                    case int(TileType::SINGLE):
                        rectPos.x = 32.0f;            
                        break;
                    
                    // all top blocks
                    case int(TileType::TOP1):
                        rectPos.x = 32.0f * 0;
                        rectPos.y = 32.0f;
                        break;
                    case int(TileType::TOP2):
                        rectPos.x = 32.0f * 1;
                        rectPos.y = 32.0f;
                        break;
                    case int(TileType::TOP3):
                        rectPos.x = 32.0f * 2;
                        rectPos.y = 32.0f;
                        break;
                    case int(TileType::TOP4):
                        rectPos.x = 32.0f * 3;
                        rectPos.y = 32.0f;
                        break;
                    case int(TileType::TOP5):
                        rectPos.x = 32.0f * 4;
                        rectPos.y = 32.0f;
                        break;
                    case int(TileType::TOP6):
                        rectPos.x = 32.0f * 5;
                        rectPos.y = 32.0f;
                        break;
                    case int(TileType::TOP7):
                        rectPos.x = 32.0f * 6;
                        rectPos.y = 32.0f;
                        break;
                    
                    // all middle blocks
                    case int(TileType::MID1):
                        rectPos.x = 32.0f * 0;
                        rectPos.y = 64.0f;
                        break;
                    case int(TileType::MID2):
                        rectPos.x = 32.0f * 1;
                        rectPos.y = 64.0f;
                        break;
                    case int(TileType::MID3):
                        rectPos.x = 32.0f * 2;
                        rectPos.y = 64.0f;
                        break;
                    case int(TileType::MID4):
                        rectPos.x = 32.0f * 3;
                        rectPos.y = 64.0f;
                        break;
                    
                    // all bottom blocks
                    case int(TileType::BOTTOM1):
                        rectPos.x = 32.0f * 0;
                        rectPos.y = 96.0f;
                        break;
                    case int(TileType::BOTTOM2):
                        rectPos.x = 32.0f * 1;
                        rectPos.y = 96.0f;
                        break;
                    case int(TileType::BOTTOM3):
                        rectPos.x = 32.0f * 2;
                        rectPos.y = 96.0f;
                        break;
                    case int(TileType::BOTTOM4):
                        rectPos.x = 32.0f * 3;
                        rectPos.y = 96.0f;
                        break;
                }

                // Create the sprite for box object
                sf::Sprite block(Resources::get(textures::LevelTiles), 
                    sf::IntRect({rectPos.x, rectPos.y},{BLOCK_SIZE, BLOCK_SIZE}));

                block.setOrigin({BLOCK_SIZE / 2.0f,BLOCK_SIZE / 2.0f});
                block.setPosition(sf::Vector2f({tiles[tile]->GetPosition().x * SCALE, 
                    tiles[tile]->GetPosition().y * SCALE}));
                tile++;
                
                window.draw(block);
            }
            else if (cell == 17)
            {
                sf::Sprite goalBall(Resources::get(textures::LevelTiles), 
                    sf::IntRect({96, 0}, {BLOCK_SIZE, BLOCK_SIZE}));
                
                goalBall.setOrigin({BLOCK_SIZE / 2.0f,BLOCK_SIZE / 2.0f});
                goalBall.setPosition(sf::Vector2f({tiles[tile]->GetPosition().x * SCALE, 
                    tiles[tile]->GetPosition().y * SCALE}));
                tile++;

                window.draw(goalBall);
            }
            if (cell == 18)
            {
                sf::Sprite deathStone(Resources::get(textures::LevelTiles), 
                    sf::IntRect({0, 384}, {BLOCK_SIZE, BLOCK_SIZE}));

                deathStone.setOrigin({BLOCK_SIZE / 2.0f,BLOCK_SIZE / 2.0f});
                deathStone.setPosition(sf::Vector2f({tiles[tile]->GetPosition().x * SCALE, 
                    tiles[tile]->GetPosition().y * SCALE}));
                tile++;

                window.draw(deathStone);
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


bool Level::playerReachedGoal(const sf::Vector2f& playerPos) const
{
    float dx = playerPos.x - goalPos.x;
    float dy = playerPos.y - goalPos.y;
    float distanceSquared = dx * dx + dy * dy;

    return distanceSquared < 900.0f; // adjust threshold for win radius
}


void Level::createBody(int x, int y)
{
    // Create the body definition
    b2BodyDef def{};
    def.position.Set(
        (BLOCK_SIZE * x + BLOCK_SIZE / 2.0f) / SCALE, 
        (BLOCK_SIZE * y + BLOCK_SIZE / 2.0f) / SCALE);

    // Create the body using pointers
    b2Body* body = world.CreateBody(&def);
    
    // Create the polygon (square) shape for visuals
    b2PolygonShape shape{};
    shape.SetAsBox(BLOCK_SIZE / 2.0f / SCALE, BLOCK_SIZE / 2.0f / SCALE);
    body->CreateFixture(&shape, 0.0f);
    
    tiles.push_back(body);
}