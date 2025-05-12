#include "Player.h"

constexpr float SCALE = 32.f; 

const float SPEED = 5.0f;
const float JUMP_HEIGHT = 7.0f;

Player::Player(sf::Vector2f pos,  textures::ID txtID) : p_txt(txtID)
{
    initAnimations();
    p_visual->setPosition(pos);

    initPhysicalBody(pos);

    for(int i = 0; i < int(move::COUNT); i++)
        heading[i] = false;

    isGrounded = 0;
    facingRight = true;

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
       facingRight = true;
    }
    else if(key == sf::Keyboard::Scan::Left)
    {
        heading[int(move::LEFT)] = true;
        facingRight = false;
    }
    else if(key == sf::Keyboard::Scan::Up)
    {
        heading[int(move::UP)] = true;
    }
    else if(key == sf::Keyboard::Scan::LShift)
    {
        heading[int(move::RUN)] = true;
    }
}


void Player::keyReleased(sf::Keyboard::Scancode key)
{
    if(key == sf::Keyboard::Scan::Right)
    {
        heading[int(move::RIGHT)] = false;
    }
    else if(key == sf::Keyboard::Scan::Left)
    {
        heading[int(move::LEFT)] = false;
    }
    else if(key == sf::Keyboard::Scan::Up)
    {
        heading[int(move::UP)] = false;
    }
    else if(key == sf::Keyboard::Scan::LShift)
    {
        heading[int(move::RUN)] = false;
    }
}


void Player::update(const float& dt)
{
    // Update the movement of player
    b2Vec2 vel = p_body->GetLinearVelocity();
    vel.x = 0.0f;

    if(heading[int(move::RIGHT)])
    {
        if(heading[int(move::RUN)])
        {
            vel.x += SPEED * 1.35f;
            curr_animation = (isGrounded) ? state::RUN_RIGHT : state::JUMP_RIGHT;
        }
        else
        {
            vel.x += SPEED;
            curr_animation = (isGrounded) ? state::WALK_RIGHT : state::JUMP_RIGHT;
        }
    }
    if(heading[int(move::LEFT)])
    {
        if(heading[int(move::RUN)])
        {
            vel.x -= SPEED * 1.35f;
            curr_animation = (isGrounded) ? state::RUN_LEFT : state::JUMP_LEFT;
        }
        else
        {
            vel.x -= SPEED;
            curr_animation = (isGrounded) ? state::WALK_LEFT : state::JUMP_LEFT;
        }
    }
    if(heading[int(move::UP)] && isGrounded)
    {
        vel.y = (heading[int(move::RUN)]) ? -JUMP_HEIGHT * 1.2f : -JUMP_HEIGHT;

        if(facingRight)
        {
            curr_animation = state::JUMP_RIGHT;
        }
        else
        {
            curr_animation = state::JUMP_LEFT;
        }
    }

    if(vel.x == 0 && vel.y == 0)
    {
        curr_animation = (facingRight) ? state::IDLE_RIGHT : state::IDLE_LEFT;
    }
    p_body->SetLinearVelocity(vel);

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


void Player::OnBeginContact()
{
    isGrounded++;
}


void Player::OnEndContact()
{
    if(isGrounded > 0)
        isGrounded--;
}


void Player::initAnimations()
{
    sf::Texture* t = &Resources::get(p_txt);
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


void Player::initPhysicalBody(sf::Vector2f pos)
{
    sf::Vector2f size;
    size.x = 16.0f;
    size.y = 16.0f;

    b2BodyDef def{};
    def.type = b2_dynamicBody;
    def.position.Set(pos.x / SCALE, pos.y / SCALE);
    def.fixedRotation = true;
    p_body = Level::world.CreateBody(&def);
    
    b2FixtureDef fixDef{};
    fixDef.density = 1.0f;
    fixDef.friction = 0.0f;
    
    b2CircleShape circleShape{};
    circleShape.m_radius = size.x / SCALE;
    circleShape.m_p.Set(0.0f, -size.x / SCALE);
    fixDef.shape = &circleShape;
    p_body->CreateFixture(&fixDef);
    
    circleShape.m_p.Set(0.0f, size.x / SCALE);
    p_body->CreateFixture(&fixDef);
    
    b2PolygonShape polyShape{};
    polyShape.SetAsBox(size.x / SCALE, size.y / SCALE);
    fixDef.shape = &polyShape;
    p_body->CreateFixture(&fixDef);
    
    polyShape.SetAsBox((size.x - 4.0f) / SCALE, (size.y * 0.2f) / SCALE, b2Vec2(0.0f, 1.0f), 0.0f);
    fixDef.userData.pointer = reinterpret_cast<uintptr_t>(this); 
    fixDef.isSensor = true;
    p_body->CreateFixture(&fixDef);
}