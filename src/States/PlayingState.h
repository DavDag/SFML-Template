#pragma once

#include "..//Network/Network.h"
#include "..//Game.h"
#include "BaseState.h"

class Widget;
class Textbox;

class PlayingState : public BaseState
{
	public:
		PlayingState(Game*, const std::string&, const std::string&, const int&);

		void handleInput() override;
		void handleEvent(const sf::Event&, const sf::RenderWindow&) override;
		void update(float) override;
		void draw(sf::RenderWindow&) override;

		void enterCallback(Textbox&);

	private:
		std::vector<Widget*> m_widgets;
		std::string m_text, m_username, m_ip;
		TCPClient m_tcpclient;

		bool m_destroy;
};