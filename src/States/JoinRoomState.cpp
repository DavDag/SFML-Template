#include "JoinRoomState.h"

#include <functional>

#include "..//Gui/Gui.h"
#include "PlayingState.h"

JoinRoomState::JoinRoomState(Game* game) :
	BaseState(game), m_widgets(4)
{
	m_widgets[0] = new Textbox(400, 75, m_room_ip);
	m_widgets[1] = new Textbox(400, 75, m_username);
	m_widgets[2] = new Button(150, 75, "ENTER");
	m_widgets[3] = new Button(150, 75, "BACK");

	m_widgets[0]->setOrigin(200, 37.5f);
	m_widgets[1]->setOrigin(200, 37.5f);
	m_widgets[2]->setOrigin(75, 37.5f);
	m_widgets[3]->setOrigin(75, 37.5f);

	m_widgets[0]->setPosition(game->getScreenSize().x * 0.5f, game->getScreenSize().y * 0.25f);
	m_widgets[1]->setPosition(game->getScreenSize().x * 0.5f, game->getScreenSize().y * 0.5f);
	m_widgets[2]->setPosition(game->getScreenSize().x * 0.66f, game->getScreenSize().y * 0.75f);
	m_widgets[3]->setPosition(game->getScreenSize().x * 0.33f, game->getScreenSize().y * 0.75f);

	m_widgets[0]->setFillColor(sf::Color::Transparent, Widget::Status::FREE);
	m_widgets[0]->setFillColor(sf::Color::Transparent, Widget::Status::HOVER);
	m_widgets[0]->setFillColor(sf::Color::Transparent, Widget::Status::CLICKED);
	m_widgets[0]->setFillColor(sf::Color::Transparent, Widget::Status::TOGGLED);

	m_widgets[1]->setFillColor(sf::Color::Transparent, Widget::Status::FREE);
	m_widgets[1]->setFillColor(sf::Color::Transparent, Widget::Status::HOVER);
	m_widgets[1]->setFillColor(sf::Color::Transparent, Widget::Status::CLICKED);
	m_widgets[1]->setFillColor(sf::Color::Transparent, Widget::Status::TOGGLED);

	m_widgets[2]->setFillColor(sf::Color::Transparent, Widget::Status::FREE);
	m_widgets[2]->setFillColor(sf::Color::Transparent, Widget::Status::HOVER);
	m_widgets[2]->setFillColor(sf::Color::Transparent, Widget::Status::CLICKED);

	m_widgets[3]->setFillColor(sf::Color::Transparent, Widget::Status::FREE);
	m_widgets[3]->setFillColor(sf::Color::Transparent, Widget::Status::HOVER);
	m_widgets[3]->setFillColor(sf::Color::Transparent, Widget::Status::CLICKED);

	((Textbox*)m_widgets[0])->setPlaceholderString("Destination IP");
	((Textbox*)m_widgets[1])->setPlaceholderString("Username");

	((Button*)m_widgets[3])->setCallback(std::bind(&JoinRoomState::backToMenu, this, std::placeholders::_1));
	((Button*)m_widgets[2])->setCallback(std::bind(&JoinRoomState::tryEnterTheRoom, this, std::placeholders::_1));
}

void JoinRoomState::backToMenu(Button& b)
{
	m_game->popState();
}

void JoinRoomState::tryEnterTheRoom(Button& b)
{
	if (m_username.empty() || m_room_ip.empty()) return;

	PlayingState* ps = new PlayingState(m_game, m_room_ip, m_username, 53535);
	m_game->pushState(std::unique_ptr<BaseState>(ps));
}

void JoinRoomState::handleInput()
{
	for (Widget* w : m_widgets) w->handleInput();
}

void JoinRoomState::handleEvent(const sf::Event& e, const sf::RenderWindow& window)
{
	for (Widget* w : m_widgets) w->handleEvent(e, window);
}

void JoinRoomState::draw(sf::RenderWindow& window)
{
	for (Widget* w : m_widgets) window.draw(*w);
}

void JoinRoomState::update(float dt)
{
	for (Widget* w : m_widgets) w->update(dt);
}