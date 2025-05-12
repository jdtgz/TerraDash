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
	level.update(dt, player->getPosition());
	player->update(dt);

	// Camera
	updateView();
}


void Game::updateView()
{
	camera.setCenter(player->getPosition());
}


void Game::render()
{
	window->clear();
	
	level.draw(*window);
	player->draw(*window);
	
	//Level::debugDraw(*window);

	window->setView(camera);
	
	window->display();
}