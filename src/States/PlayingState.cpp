#include "JoinRoomState.h"

#include <iostream>
#include <functional>

#include "..//Gui/Gui.h"
#include "PlayingState.h"

PlayingState::PlayingState(Game* game, const std::string& ip, const std::string& username, const int& port) :
	BaseState(game), m_widgets(1), m_text(""), m_username(username), m_ip(ip), m_destroy(false)
{
	m_widgets[0] = new Textbox(400, 100, m_text);
	m_widgets[0]->setOrigin(200, 50);
	m_widgets[0]->setPosition(m_game->getScreenSize().x * 0.5f, m_game->getScreenSize().y * 0.5f);

	m_widgets[0]->setFillColor(sf::Color::Transparent, Widget::Status::FREE);
	m_widgets[0]->setFillColor(sf::Color::Transparent, Widget::Status::HOVER);
	m_widgets[0]->setFillColor(sf::Color::Transparent, Widget::Status::CLICKED);
	m_widgets[0]->setFillColor(sf::Color::Transparent, Widget::Status::TOGGLED);

	((Textbox*)m_widgets[0])->setCallback(std::bind(&PlayingState::enterCallback, this, std::placeholders::_1));
	m_destroy = !m_tcpclient.connect(ip, port);

	if (!m_destroy) m_tcpclient.sendMessage(username);
}

void PlayingState::enterCallback(Textbox& t)
{
	std::cout << "TRYING TO SEND : " << m_text << "\n";
	if (!m_text.empty() && !m_tcpclient.sendMessage(m_text))	std::cout << "[FAILURE]\n";
	else														std::cout << "[SUCCESS]\n";
}

void PlayingState::handleInput()
{
	for (Widget* w : m_widgets) w->handleInput();
}

void PlayingState::handleEvent(const sf::Event& e, const sf::RenderWindow& window)
{
	for (Widget* w : m_widgets) w->handleEvent(e, window);
}

void PlayingState::draw(sf::RenderWindow& window)
{
	for (Widget* w : m_widgets) window.draw(*w);
}

void PlayingState::update(float dt)
{
	if (m_destroy)
	{
		std::cout << "FAILED TO CONNECT TO : " << m_ip << " [53535]\n";
		m_game->popState();
		return;
	}
	
	for (Widget* w : m_widgets) w->update(dt);
}