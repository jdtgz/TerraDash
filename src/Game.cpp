#include "Game.h"

Game::Game()
{
	window = new sf::RenderWindow(sf::VideoMode({ 1000, 1000 }), "Super Ultimate Speedrunners Game");
	
	player = new sf::RectangleShape();
	player->setSize(sf::Vector2f(100, 50));
	player->setOutlineColor(sf::Color::Red);
	player->setOutlineThickness(5);
	player->setPosition({10, 20});
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

	window->display();
}