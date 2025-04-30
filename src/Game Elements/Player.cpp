#include "Player.h"


Player::Player()
{
    initAnimations();
}


Player::~Player()
{
    delete p_visual;
}


void Player::keyPressed(const sf::Keyboard::Key& key)
{
    switch(key)
    {
        default:
            std::cout << "ERROR: detected invalid movement.";
    }
}


void Player::update(const float& dt)
{
    p_animations[int(curr_animation)].update(dt);
    p_animations[int(curr_animation)].applyToSprite(*p_visual);
}


void Player::draw(sf::RenderWindow& window) const
{
    window.draw(*p_visual);
}


void Player::initAnimations()
{
    sf::Texture* t = &Resources::get(textures::Pink);
    p_visual = new sf::Sprite(*t);

    sf::Vector2i size({32, 32});
    sf::Vector2i pos({0, 32});

    // Initialize all rect for each frame for every animation in player
    p_animations[int(anim_index::IDLE)].setUp(*t, pos.x, pos.y * 1, size.x, size.y, 4);
    p_animations[int(anim_index::WALK_RIGHT)].setUp(*t, pos.x, pos.y * 2, size.x, size.y, 6);
    p_animations[int(anim_index::WALK_LEFT)].setUp(*t, pos.x, pos.y * 3, size.x, size.y, 6);
    p_animations[int(anim_index::RUN_RIGHT)].setUp(*t, pos.x, pos.y * 4, size.x, size.y, 6);
    p_animations[int(anim_index::RUN_LEFT)].setUp(*t, pos.x, pos.y * 5, size.x, size.y, 6);
    p_animations[int(anim_index::JUMP_RIGHT)].setUp(*t, pos.x, pos.y * 6, size.x, size.y, 8);
    p_animations[int(anim_index::JUMP_LEFT)].setUp(*t, pos.x, pos.y * 7, size.x, size.y, 8);
    p_animations[int(anim_index::HURT)].setUp(*t, pos.x, pos.y * 8, size.x, size.y, 4);
    p_animations[int(anim_index::DEATH)].setUp(*t, pos.x, pos.y * 9, size.x, size.y, 8);    
    
    // Set first frame for all animation to be the first one 
    for(int i = 0; i < int(anim_index::COUNT); i++)
        p_animations[i].setFrame(0);
    
    // Start player with the idle animation and set his position
    curr_animation = anim_index::IDLE;
    p_animations[int(curr_animation)].applyToSprite(*p_visual);
    p_visual->setPosition({50, 100});
}