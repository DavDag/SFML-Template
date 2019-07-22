#pragma once

#include <SFML/Graphics.hpp>

class Game;

class BaseState
{
	public:
		BaseState(Game* game) { m_game = game; }

		virtual void handleInput() = 0;
		virtual void handleEvent(const sf::Event&, const sf::RenderWindow&) = 0;
		virtual void update(float) = 0;
		virtual void draw(sf::RenderWindow&) = 0;

	protected:
		Game* m_game;
};