#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "BaseState.h"

class Button;
class Widget;

class MenuState : public BaseState
{
	public:
		MenuState(Game*);

		void handleInput() override;
		void handleEvent(const sf::Event&, const sf::RenderWindow&) override;
		void update(float) override;
		void draw(sf::RenderWindow&) override;

		void createRoom(Button&);
		void joinRoom(Button&);

	private:
		std::vector<Widget*> m_widgets;
};