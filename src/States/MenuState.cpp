#include "MenuState.h"

#include <iostream>

#include "..//Game.h"
#include "../Gui/Gui.h"
#include "..//ResourceManager/ResourceHolder.h"
#include "JoinRoomState.h"
#include "CreateRoomState.h"

MenuState::MenuState(Game* game):
	BaseState(game), m_widgets(2)
{
	m_widgets[0] = new Button(200, 100, "Create Room");
	m_widgets[1] = new Button(200, 100, "Join Room");

	m_widgets[0]->setPosition(game->getScreenSize().x * 0.25f, game->getScreenSize().y * 0.5f);
	m_widgets[1]->setPosition(game->getScreenSize().x * 0.75f, game->getScreenSize().y * 0.5f);

	m_widgets[0]->setOrigin(100, 50);
	m_widgets[1]->setOrigin(100, 50);

	m_widgets[0]->setFillColor(sf::Color::Transparent, Widget::Status::FREE);
	m_widgets[0]->setFillColor(sf::Color::Transparent, Widget::Status::HOVER);
	m_widgets[0]->setFillColor(sf::Color::Transparent, Widget::Status::CLICKED);

	m_widgets[1]->setFillColor(sf::Color::Transparent, Widget::Status::FREE);
	m_widgets[1]->setFillColor(sf::Color::Transparent, Widget::Status::HOVER);
	m_widgets[1]->setFillColor(sf::Color::Transparent, Widget::Status::CLICKED);

	((Button*)m_widgets[0])->setCallback(std::bind(&MenuState::createRoom, this, std::placeholders::_1));
	((Button*)m_widgets[1])->setCallback(std::bind(&MenuState::joinRoom, this, std::placeholders::_1));
}

void MenuState::createRoom(Button& b)
{
	CreateRoomState* cs = new CreateRoomState(m_game, 53535);
	m_game->pushState(std::unique_ptr<BaseState>(cs));
}

void MenuState::joinRoom(Button& b)
{
	JoinRoomState* js = new JoinRoomState(m_game);
	m_game->pushState(std::unique_ptr<BaseState>(js));
}

void MenuState::handleInput()
{
	for (Widget* w : m_widgets) w->handleInput();
}

void MenuState::handleEvent(const sf::Event& e, const sf::RenderWindow& window)
{
	for (Widget* w : m_widgets) w->handleEvent(e, window);
}

void MenuState::draw(sf::RenderWindow& window)
{
	for (Widget* w : m_widgets) window.draw(*w);
}

void MenuState::update(float dt)
{
	for (Widget* w : m_widgets) w->update(dt);
}