#pragma once

#include "..//Network/Network.h"
#include "..//Game.h"
#include "BaseState.h"

class Widget;
class Textbox;

class CreateRoomState : public BaseState
{
	public:
		CreateRoomState(Game*, const int& port);

		void handleInput() override;
		void handleEvent(const sf::Event&, const sf::RenderWindow&) override;
		void update(float) override;
		void draw(sf::RenderWindow&) override;

	private:
		std::vector<Widget*> m_widgets;
		std::string m_text, m_username;
		Server m_server;

		bool m_destroy;
};