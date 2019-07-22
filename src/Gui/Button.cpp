#include "Button.h"

#include <iostream>

#include "../ResourceManager/ResourceHolder.h"

Button::Button(int width, int height, const std::string& text):
	Widget(width, height, Button::Status::FREE), m_tcolor(sf::Color::White), m_tsize(30), m_text(text)
{
	m_callback	= NULL;
}

void Button::handleInput()
{
}

void Button::handleEvent(const sf::Event& e, const sf::RenderWindow& window)
{
	sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	bool clicked = m_status == Widget::Status::CLICKED;
	Widget::updateStatus(e, mousePos);

	if (clicked && m_status != Widget::Status::CLICKED && m_callback != NULL) m_callback(*this);
}

void Button::update(float dt)
{
}

void Button::draw(sf::RenderTarget& rt, sf::RenderStates rs) const
{
	sf::RectangleShape rect(sf::Vector2f((float)m_width, (float)m_height));
	rect.setFillColor(m_fcolors[m_status - 1]);
	rect.setOutlineColor(m_bcolors[m_status - 1]);
	rect.setOutlineThickness((float)m_bsize);
	sf::Text text(m_text, ResourceHolder::get().fonts.get("default"));
	sf::FloatRect textRect = text.getLocalBounds();
	text.setFillColor(m_tcolor);
	text.setCharacterSize(m_tsize);
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	text.setPosition(m_width / 2.0f, m_height / 2.0f);

	rs.texture = NULL;
	rs.transform *= getTransform();
	rt.draw(rect, rs);
	rt.draw(text, rs);
}
