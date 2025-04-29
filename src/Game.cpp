#include "Game.h"

Game::Game()
{
	window = new sf::RenderWindow(sf::VideoMode({ 1200, 900 }), "TerraDash");
	window->setFramerateLimit(144);

	player = new sf::Sprite(Resources::get(textures::Blue));
	player->setTextureRect(sf::IntRect({0, 0}, {32 ,32}));
	player->setPosition({50, 50});
	player->setScale({3,3});

	sf::Image world;
	world.loadFromFile("Textures/world1.png");
	level.createFromImage(world);
}


Game::~Game()
{
	delete window;
	delete player;
}


void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastTick = sf::Time::Zero;

	while (window->isOpen())
	{
		processEvents();

		// advance clock
		timeSinceLastTick += clock.restart();

		while (timeSinceLastTick > timePerFrame)
		{
			timeSinceLastTick -= timePerFrame;
			processEvents();
			update(timeSinceLastTick);
		}
		render();
	}
}


void Game::processEvents()
{
	while (const std::optional event = window->pollEvent())
	{
		if (event->is<sf::Event::Closed>())
			window->close();
	}
}


void Game::update(const sf::Time& dt)
{
}


void Game::render()
{
	window->clear();

	window->draw(*player);
	level.draw(*window);
	
	window->display();
}