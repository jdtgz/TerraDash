#include "Player.h"

constexpr float SCALE = 30.f; 

Player::Player(sf::Vector2f pos)
{
    initAnimations();
    p_visual->setPosition(pos);

    b2BodyDef def{};
    def.type = b2_dynamicBody;
    def.position.Set(pos.x / SCALE, pos.y / SCALE);
    
    p_body = Level::world.CreateBody(&def);
    
    b2PolygonShape shape{};
    shape.SetAsBox(16.0f / SCALE, 32.0f / SCALE);
    
    b2FixtureDef fixDef{};
    fixDef.shape = &shape;
    fixDef.density = 1.0f;
    fixDef.friction = 0.3f;
    p_body->CreateFixture(&fixDef);

    p_body->SetFixedRotation(true);
    p_body->SetLinearDamping(1.0f);

    for(int i = 0; i < int(move::COUNT); i++)
        heading[i] = false;

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
    }
    if(key == sf::Keyboard::Scan::Left)
    {
        heading[int(move::LEFT)] = true;
    }
    if(key == sf::Keyboard::Scan::Up)
    {
        heading[int(move::IN_AIR)] = true;
    }
    
}


void Player::keyReleased(sf::Keyboard::Scancode key)
{
    if(key == sf::Keyboard::Scan::Right)
    {
        heading[int(move::RIGHT)] = false;
    }
    if(key == sf::Keyboard::Scan::Left)
    {
        heading[int(move::LEFT)] = false;
    }
    if(key == sf::Keyboard::Scan::Up)
    {
        heading[int(move::IN_AIR)] = false;
    }
}


void Player::update(const float& dt)
{
    // Update the movement of player
    b2Vec2 force (0.0f, 0.0f);
    if(heading[int(move::RIGHT)])
        force.x += 70.f;
    if(heading[int(move::LEFT)])
        force.x -= 70.f;
    if(heading[int(move::IN_AIR)])
        force.y -= 100.f;

    p_body->ApplyForceToCenter(force, true);

    b2Vec2 nPos = p_body->GetPosition();
    p_visual->setPosition(sf::Vector2f({nPos.x * SCALE, nPos.y * SCALE}));
    
    // Update animation visuals
    p_animations[int(curr_animation)].update(dt);
    p_animations[int(curr_animation)].applyToSprite(*p_visual);
}


void Player::draw(sf::RenderWindow& window) const
{    
    window.draw(*p_visual);
}


sf::Vector2f Player::getPosition() const
{
    b2Vec2 cPos = p_body->GetPosition();
    return sf::Vector2f({cPos.x * SCALE, cPos.y * SCALE});
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