#include "Game.h"


Game::Game(textures::ID p_id)
{
	window = new sf::RenderWindow(sf::VideoMode({ 1920, 1080 }), "TerraDash");
	window->setFramerateLimit(144);

	// Init world and player 
	sf::Image lvl;
	if(!lvl.loadFromFile("Textures/Worlds/world1.png"))
		std::cerr << "Could not load image." << std::endl;

	player = new Player(level.createFromImage(lvl), p_id);

	// Init camera centered about player
	camera.setSize(window->getDefaultView().getSize());
	camera.setCenter(player->getPosition());
	camera.zoom(0.75f);

	// Game state and timer
	score = 1000;
	timer.restart();
	state = GameState::PLAYING;

	
	font = new sf::Font(("Textures/Fonts/Michelin Bold.ttf"));
	scoreText = new sf::Text(*font);
	scoreText->setCharacterSize(24);
	scoreText->setFillColor(sf::Color::White);
	scoreText->setPosition({100, 100});

	gameOverText = new sf::Text(*font);
	gameOverText->setCharacterSize(36);
	gameOverText->setFillColor(sf::Color::Red);
	gameOverText->setString("Game Over\nPress Enter to return");
	gameOverText->setPosition({600, 400});

	winText = new sf::Text(*font);
	winText->setFont(*font);
	winText->setCharacterSize(36);
	winText->setFillColor(sf::Color::Green);
	winText->setString("You Win!\nPress Enter to return");
	winText->setPosition({600, 400});
}


Game::~Game()
{
	delete window;
	delete player;
	delete font;
	delete gameOverText;
	delete scoreText;
	delete winText;
}


void Game::run()
{
	sf::Clock clock;

	while (window->isOpen())
	{
		float deltaTime = clock.restart().asSeconds();

		processEvents();

		if (state == GameState::PLAYING)
			update(deltaTime);

		render();
	}
}

void Game::processEvents()
{
	while (const std::optional event = window->pollEvent())
	{
		if (event->is<sf::Event::Closed>())
		{
			window->close();
		}
		else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
		{
			player->keyPressed(keyPressed->scancode);

			if((state == GameState::GAME_OVER || state == GameState::WIN) && 
					keyPressed->scancode == sf::Keyboard::Scancode::Enter)
			{
				state = GameState::EXIT;
				window->close();
			}
		}
		else if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>())
		{
			player->keyReleased(keyReleased->scancode);
		}
	}
}

void Game::update(const float dt)
{
	score = 1000 - static_cast<int>(timer.getElapsedTime().asSeconds());
	if (score < 0) score = 0;
	scoreText->setString("Score: " + std::to_string(score));

	//Lock the ScoreText in place
	scoreText->setPosition(window->mapPixelToCoords(sf::Vector2i(20,20), window->getDefaultView()));

	level.update(dt, player->getPosition());
	player->update(dt);
	checkGameConditions();
	updateView();
}


void Game::updateView()
{
	camera.setCenter(player->getPosition());
	window->setView(camera);
}

void Game::render()
{
	window->clear();
	level.draw(*window);
	player->draw(*window);
	
	//Level::debugDraw(*window);

	if (state == GameState::PLAYING)
		drawOverlay(*scoreText);
	else if (state == GameState::GAME_OVER)
	{
		sf::Sprite gameOverScreen(Resources::get(textures::GameOver));
		gameOverScreen.setTextureRect(sf::IntRect({ 0, 0 }, { 1092, 1080 }));
    	gameOverScreen.setOrigin({ 860.0f, 540.0f });
    	gameOverScreen.setPosition({ 860.0f, 540.0f });

		window->draw(gameOverScreen);
	}
	else if (state == GameState::WIN)
	{
		sf::Sprite gameWinScreen(Resources::get(textures::GameWin));
		gameWinScreen.setTextureRect(sf::IntRect({ 0, 0 }, { 1092, 1080 }));
    	gameWinScreen.setOrigin({ 860.0f, 540.0f });
    	gameWinScreen.setPosition({ 860.0f, 540.0f });

		window->draw(gameOverScreen);
	}

	window->display();
}


void Game::drawOverlay(const sf::Text& text)
{
	window->setView(window->getDefaultView());
	window->draw(text);
	window->setView(camera);
}


void Game::checkGameConditions()
{
	// Win check happens first — reaching goal wins immediately
	if (state == GameState::PLAYING && level.playerReachedGoal(player->getPosition()))
	{
		state = GameState::WIN;
		return; // Prevents Game Over from overriding it
	}

	// Game over due to health or deadly block
	if (state == GameState::PLAYING &&
		(player->getHealth() <= 0 || Level::playerHitDeadly))
	{
		state = GameState::GAME_OVER;
	}

	Level::playerHitDeadly = false;
}
