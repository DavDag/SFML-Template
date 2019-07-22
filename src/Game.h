#pragma once

#include <memory>
#include <stack>
#include <string>
#include <SFML/Graphics.hpp>

#include "States/BaseState.h"

class Game
{
	public:
		Game(int, int, const std::string&);
		
		void run();

		void pushState(std::unique_ptr<BaseState> state);
		void popState();
		BaseState& getCurrentState();
		void exitGame();

		sf::Vector2f getScreenSize() const { return sf::Vector2f((float)m_width, (float)m_height); }

	private:
		void handleEvents();

	private:
		sf::RenderWindow m_window;

		int m_width, m_height;
		std::string m_title;

		std::stack<std::unique_ptr<BaseState>> m_queue;
};