#pragma once

#include <SFML/Graphics.hpp>
#include "Level.h"
#include "Player.h"
#include "Animation.h"
#include "Resources.h"

enum class GameState {
    MENU,
    PLAYING,
    GAME_OVER,
    WIN,
    EXIT
};

class Game
{
public:
    Game(textures::ID p_id);
    ~Game();

    void run();
    GameState getState() const { return state; }

private:
    void processEvents();
    void update(const float dt);
    void updateView();
    void render();

    void drawOverlay(const sf::Text& text);
    void checkGameConditions();

    // Window Elements
    sf::RenderWindow* window;
    sf::View camera;

    // Game Elements
    Player* player;
    Level level;

    // Game State
    GameState state;

    // Timer and Score
    int score;
    sf::Clock timer;
    sf::Font *font;
    sf::Text *scoreText;
    sf::Text *gameOverText;
    sf::Text *winText;
};