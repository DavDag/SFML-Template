#pragma once

#include "..//Game.h"
#include "BaseState.h"

class Widget;
class Button;

class JoinRoomState : public BaseState
{
	public:
		JoinRoomState(Game*);

		void handleInput() override;
		void handleEvent(const sf::Event&, const sf::RenderWindow&) override;
		void update(float) override;
		void draw(sf::RenderWindow&) override;

		void backToMenu(Button&);
		void tryEnterTheRoom(Button& b);

	private:
		std::vector<Widget*> m_widgets;
		std::string m_room_ip;
		std::string m_username;
};