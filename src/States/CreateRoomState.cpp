#include "CreateRoomState.h"

#include <iostream>
#include <functional>

#include "..//Gui/Gui.h"

CreateRoomState::CreateRoomState(Game* game, const int& port) :
	BaseState(game), m_widgets(0), m_destroy(false)
{
	m_destroy = !m_server.bind("192.168.1.126", port);
}

void CreateRoomState::handleInput()
{
	for (Widget* w : m_widgets) w->handleInput();
}

void CreateRoomState::handleEvent(const sf::Event& e, const sf::RenderWindow& window)
{
	for (Widget* w : m_widgets) w->handleEvent(e, window);
}

void CreateRoomState::draw(sf::RenderWindow& window)
{
	for (Widget* w : m_widgets) window.draw(*w);
}

void CreateRoomState::update(float dt)
{
	if (m_destroy)
	{
		std::cout << "FAILED TO BIND SERVER";
		m_game->popState();
		return;
	}

	if (m_server.getNumUsers() == 1)
	{
		std::string msg = m_server.readMessage(0);
		if (!msg.empty()) std::cout << msg << "\n";
	}
	else
	{
		m_server.waitUser();
		std::string msg = m_server.readMessage(0);
		if (!msg.empty()) std::cout << "Utente " << msg << " Connesso\n";
	}

	for (Widget* w : m_widgets) w->update(dt);
}