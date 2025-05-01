#include "Game.h"


Game::Game()
{
	window = new sf::RenderWindow(sf::VideoMode({ 1200, 900 }), "TerraDash");
	window->setFramerateLimit(144);

	level.init();
	
	sf::Image lvl;
	lvl.loadFromFile("Textures/Worlds/world1.png");
	player = new Player(level.createFromImage(lvl));
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
	player->update(dt);
	level.update(dt);
}


void Game::updateView()
{
	float aspect = (float)window->getSize().x / (float)window->getSize().y;

	sf::Vector2f size;
	if(aspect < 1.0f)
	{
		size = sf::Vector2f(ZOOM, ZOOM / aspect);
	}
	else
	{
		size = sf::Vector2f(ZOOM * aspect, ZOOM);
	}
	camera.setSize(size);
}


void Game::render()
{
	window->clear();
	
	//window->setView(camera);
	player->draw(*window);
	level.draw(*window);
	
	window->display();
}