#include "Player.h"


Player::Player(sf::Vector2f pos)
{
    std::cout << "Position from image file: (" << pos.x << ", " << pos.y << ")\n";
    initAnimations();
    p_visual->setPosition(pos);

    b2BodyDef def{};
    def.type = b2_dynamicBody;
    def.position.Set(pos.x, pos.y);
    
    body = Level::world.CreateBody(&def);
    
    b2PolygonShape shape{};
    shape.SetAsBox(0.5f, 1.0f);
    
    b2FixtureDef fixDef{};
    fixDef.shape = &shape;
    fixDef.density = 1.0f;
    fixDef.friction = 0.3f;
    body->CreateFixture(&fixDef);

    // set heading to face right by default
    heading[int(move::RIGHT)] = true;
    heading[int(move::LEFT)] = false;
    heading[int(move::IN_AIR)] = false;

    // Set all movement to false since player is not initially moving
    for(int i = 0; i < int(state::COUNT); i++)
        key_movement[i] = false;

    hp = 10;
}


Player::~Player()
{
    delete p_visual;
}


void Player::keyPressed(sf::Keyboard::Scancode key)
{
    if(key == sf::Keyboard::Scan::Right)
    {
        heading[int(move::RIGHT)] = true;
        heading[int(move::LEFT)] = false;
        key_movement[int(state::IDLE_RIGHT)] = false;
        
        if(heading[int(move::IN_AIR)])
        {
            key_movement[int(state::JUMP_RIGHT)] = true;
            curr_animation = state::JUMP_RIGHT;
        }
        else
        {
            key_movement[int(state::WALK_RIGHT)] = true;
            curr_animation = state::WALK_RIGHT;
        }
    }
    else if(key == sf::Keyboard::Scan::Left)
    {
        heading[int(move::LEFT)] = true;
        heading[int(move::RIGHT)] = false;
        key_movement[int(state::IDLE_LEFT)] = false;

        if(heading[int(move::IN_AIR)])
        {
            key_movement[int(state::JUMP_LEFT)] = true;
            curr_animation = state::JUMP_LEFT;
        }
        else
        {
            key_movement[int(state::WALK_LEFT)] = true;
            curr_animation = state::WALK_LEFT;
        }
    }
    else if(key == sf::Keyboard::Scan::Space || key == sf::Keyboard::Scan::Up)
    {
        heading[int(move::IN_AIR)] = true;

        if(heading[int(move::RIGHT)])
        {
            key_movement[int(state::JUMP_RIGHT)] = true;
            curr_animation = state::JUMP_RIGHT;
        }
        else
        {
            key_movement[int(state::JUMP_LEFT)] = true;
            curr_animation = state::JUMP_LEFT;
        }
    }
    else if(key == sf::Keyboard::Scan::Z)
    {

    }
}


void Player::keyReleased(sf::Keyboard::Scancode key)
{
    if(key == sf::Keyboard::Scan::Right)
    {
        curr_animation = state::IDLE_RIGHT;
    }
    else if(key == sf::Keyboard::Scan::Left)
    {
        curr_animation = state::IDLE_LEFT;
    }
    else if(key == sf::Keyboard::Scan::Space || key == sf::Keyboard::Scan::Up)
    {
        heading[int(move::IN_AIR)] = false;

        if(heading[int(move::RIGHT)])
            curr_animation = state::IDLE_RIGHT;
        else 
            curr_animation = state::IDLE_LEFT;
    }
    else if(key == sf::Keyboard::Scan::Z)
    {

    }
}


void Player::update(const float& dt)
{
    p_visual->setPosition(sf::Vector2f({body->GetPosition().x, body->GetPosition().y}));
    p_animations[int(curr_animation)].update(dt);
    p_animations[int(curr_animation)].applyToSprite(*p_visual);
}


void Player::draw(sf::RenderWindow& window) const
{
    sf::RectangleShape s(sf::Vector2f({32.0f, 32.0f}));
    s.setPosition(sf::Vector2f({body->GetPosition().x, body->GetPosition().y}));
    s.setFillColor(sf::Color::Transparent);
    s.setOutlineThickness(1);
    s.setOutlineColor(sf::Color::Red);

    window.draw(*p_visual);
    window.draw(s);
}


void Player::initAnimations()
{
    sf::Texture* t = &Resources::get(textures::White);
    p_visual = new sf::Sprite(*t);

    sf::Vector2i size({32, 32});
    sf::Vector2i pos({0, 32});

    // Init each rect for all animations
    // IDLE
    p_animations[int(state::IDLE_RIGHT)].setUp(*t, pos.x, pos.y * 1, size.x, size.y, 4);
    p_animations[int(state::IDLE_LEFT)].setUp(*t, pos.x, pos.y * 2, size.x, size.y, 4);

    // WALKING
    p_animations[int(state::WALK_RIGHT)].setUp(*t, pos.x, pos.y * 3, size.x, size.y, 6);
    p_animations[int(state::WALK_LEFT)].setUp(*t, pos.x, pos.y * 4, size.x, size.y, 6);

    // RUNNING
    p_animations[int(state::RUN_RIGHT)].setUp(*t, pos.x, pos.y * 5, size.x, size.y, 6);
    p_animations[int(state::RUN_LEFT)].setUp(*t, pos.x, pos.y * 6, size.x, size.y, 6);

    // JUMPING
    p_animations[int(state::JUMP_RIGHT)].setUp(*t, pos.x, pos.y * 7, size.x, size.y, 8);
    p_animations[int(state::JUMP_LEFT)].setUp(*t, pos.x, pos.y * 8, size.x, size.y, 8);

    // HURT
    p_animations[int(state::HURT_RIGHT)].setUp(*t, pos.x, pos.y * 9, size.x, size.y, 4);
    p_animations[int(state::HURT_LEFT)].setUp(*t, pos.x, pos.y * 9, size.x, size.y, 4);

    // DEAD
    p_animations[int(state::DEATH_RIGHT)].setUp(*t, pos.x, pos.y * 11, size.x, size.y, 8);
    p_animations[int(state::DEATH_LEFT)].setUp(*t, pos.x, pos.y * 11, size.x, size.y, 8);     
    
    // Set first frame for all animation to be the first one 
    for(int i = 0; i < int(state::COUNT); i++)
        p_animations[i].setFrame(0);
    
    // Start player with the idle animation and set his position
    curr_animation = state::IDLE_RIGHT;
    p_animations[int(curr_animation)].applyToSprite(*p_visual);
}