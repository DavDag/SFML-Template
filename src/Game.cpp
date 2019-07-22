#include "Game.h"

#include "ResourceManager/ResourceHolder.h"
#include "States/MenuState.h"

Game::Game(int width, int height, const std::string& title):
	m_width(width), m_height(height), m_title(title),
	m_window(sf::VideoMode(width, height), title)
{
	MenuState* ms = new MenuState(this);
	pushState(std::unique_ptr<BaseState>(ms));

	m_window.setFramerateLimit(60);

	ResourceHolder::loadAll();
}

void Game::run()
{
	sf::Clock clock;
	clock.restart();

	while(m_window.isOpen())
	{
		BaseState& s = getCurrentState();

		s.handleInput();
		s.update(clock.restart().asSeconds());

		m_window.clear();
		s.draw(m_window);
		m_window.display();

		handleEvents();
	}
}

void Game::handleEvents()
{
	sf::Event e;
	BaseState& s = getCurrentState();

	while (m_window.pollEvent(e))
	{
		s.handleEvent(e, m_window);
		switch (e.type)
		{
			case sf::Event::Closed:
			{
				m_window.close();
				break;
			}
			default:
			{
				break;
			}
		}
	}
}

void Game::pushState(std::unique_ptr<BaseState> state)
{
	m_queue.push(std::move(state));
}

void Game::popState()
{
	if (!m_queue.empty())
	{
		m_queue.pop();
	}
}

BaseState& Game::getCurrentState()
{
	return *m_queue.top();
}

void Game::exitGame()
{

}