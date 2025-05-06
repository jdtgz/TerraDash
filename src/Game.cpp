#include "Game.h"

Game::Game()
{
	// Create the game window
	window = new sf::RenderWindow(sf::VideoMode({ 1200, 900 }), "TerraDash");
	window->setFramerateLimit(144);

	// Initialize the level
	sf::Image lvl;
	if(!lvl.loadFromFile("Textures/Worlds/world1.png"))
		std::cerr << "Could not load image." << std::endl;
	
	// Create and initialize the player 
	player = new Player(level.createFromImage(lvl));
	
	// Set up the view centered to player
	camera.setSize(window->getDefaultView().getSize());
	camera.setCenter(player->getPosition());
	camera.zoom(0.75f);
}


Game::~Game()
{
	delete window;
	delete player;
}


void Game::run()
{
	sf::Clock clock;

	while (window->isOpen())
	{
		processEvents();

		// advance clock
		float deltaTime = clock.restart().asSeconds();

		processEvents();
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
		}
		else if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>())
		{
			player->keyReleased(keyReleased->scancode);		
		}
	}
}


void Game::update(const float dt)
{
	// Game elements 
	player->update(dt);
	level.update(dt);

	// update the view of window
	updateView();
}


void Game::updateView()
{
	camera.setCenter(player->getPosition());
}


void Game::render()
{
	window->clear();
	
	player->draw(*window);
	level.draw(*window);
	
	if(false)
		Level::debugDraw(*window);

	sf::CircleShape s(1.0f);
	s.setFillColor(sf::Color::Red);
	s.setPosition({0,0});
	window->draw(s);
	window->setView(camera);
	
	window->display();
}