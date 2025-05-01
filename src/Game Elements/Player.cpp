#include "Player.h"


Player::Player(sf::Vector2f p_pos) : pos(p_pos)
{
    initAnimations();

    // Create the body definition
    b2BodyDef def{};
    def.type = b2_dynamicBody;
    def.position.Set(pos.x / SCALE, pos.y / SCALE);

    // Create the body using pointers
    body = Level::world.CreateBody(&def);

    // Create the polygon (square) shape for visuals
    b2PolygonShape shape{};
    shape.SetAsBox(0.5f, 1.0f);

    b2FixtureDef fixDef{};
    fixDef.shape = &shape;
    fixDef.density = 1.0f;
    fixDef.friction = 0.3f;
    body->CreateFixture(&fixDef);

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
        // Right key press detected, player is no longer idle
        key_movement[int(state::IDLE_RIGHT)] = false;

        // Player not running or jumping, must be walking right
        if(!key_movement[int(state::RUN_RIGHT)] && !key_movement[int(state::JUMP_RIGHT)])
        {
            key_movement[int(state::WALK_RIGHT)] = true;
            curr_animation = state::WALK_RIGHT;
        }
        // Player not walking or jumping, must be running right
        else if(!key_movement[int(state::WALK_RIGHT)] && !key_movement[int(state::JUMP_RIGHT)])
        {
            key_movement[int(state::RUN_RIGHT)] = true;
            curr_animation = state::WALK_RIGHT;
        }
        // player not walking or running, must be jumping
        else if(!key_movement[int(state::WALK_RIGHT)] && !key_movement[int(state::RUN_RIGHT)])
        {
            key_movement[int(state::JUMP_RIGHT)] = true;
            curr_animation = state::WALK_RIGHT;
        }
    }
    if(key == sf::Keyboard::Scan::Left)
    {
        // Left key press detected, player is no longer idle
        key_movement[int(state::IDLE_LEFT)] = false;

        // Player not running or jumping, must be walking right
        if(!key_movement[int(state::RUN_LEFT)] && !key_movement[int(state::JUMP_LEFT)])
        {
            key_movement[int(state::WALK_LEFT)] = true;
            curr_animation = state::WALK_LEFT;
        }
        // Player not walking or jumping, must be running right
        else if(!key_movement[int(state::WALK_LEFT)] && !key_movement[int(state::JUMP_LEFT)])
        {
            key_movement[int(state::RUN_LEFT)] = true;
            curr_animation = state::WALK_LEFT;
        }
        // player not walking or running, must be jumping
        else if(!key_movement[int(state::WALK_LEFT)] && !key_movement[int(state::RUN_LEFT)])
        {
            key_movement[int(state::JUMP_LEFT)] = true;
            curr_animation = state::WALK_LEFT;
        }
    }
    if(key == sf::Keyboard::Scan::Space)
    {
        if(key_movement[int(state::IDLE_RIGHT)])
        {
            key_movement[int(state::IDLE_RIGHT)] = false;
            key_movement[int(state::JUMP_RIGHT)] = true;
            curr_animation = state::JUMP_RIGHT;
        }
    }
}


void Player::keyReleased(sf::Keyboard::Scancode key)
{

    if(key == sf::Keyboard::Scan::Right)
    {
        // Right key release detected, player is idle
        key_movement[int(state::IDLE_RIGHT)] = true;
        
        // Player is not moving at right if right key is released
        key_movement[int(state::WALK_RIGHT)] = false;
        key_movement[int(state::RUN_RIGHT)] = false;
        key_movement[int(state::JUMP_RIGHT)] = false;

        curr_animation = state::IDLE_RIGHT;
    }
    
    if(key == sf::Keyboard::Scan::Left)
    {
        // Left key release detected, player is idle
        key_movement[int(state::IDLE_LEFT)] = true;

        // Player is not moving at left if left key is released
        key_movement[int(state::WALK_LEFT)] = false;
        key_movement[int(state::RUN_LEFT)] = false;
        key_movement[int(state::JUMP_LEFT)] = false;

        curr_animation = state::IDLE_LEFT;
    }
    
    if(key == sf::Keyboard::Scan::Space)
    {
        if(key_movement[int(state::IDLE_RIGHT)])
        {
            key_movement[int(state::IDLE_RIGHT)] = true;
            key_movement[int(state::JUMP_RIGHT)] = false;
            curr_animation = state::IDLE_RIGHT;
        }
    }
}


void Player::update(const float& dt)
{
    pos = sf::Vector2f({body->GetPosition().x * SCALE, body->GetPosition().y * SCALE});
    
    s.setSize({32.0f, 32.0f});
    s.setFillColor(sf::Color::Transparent);
    s.setOutlineThickness(1);
    s.setOutlineColor(sf::Color::Red);
    s.setPosition(pos);


    p_visual->setPosition(pos);
    p_animations[int(curr_animation)].update(dt);
    p_animations[int(curr_animation)].applyToSprite(*p_visual);
}


void Player::draw(sf::RenderWindow& window) const
{
    window.draw(*p_visual);
    window.draw(s);
}


void Player::setPos(sf::Vector2f pos)
{
    p_visual->setPosition(pos);
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