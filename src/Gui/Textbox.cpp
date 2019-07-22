#include "Textbox.h"

#include "../ResourceManager/ResourceHolder.h"

Textbox::Textbox(int width, int height, std::string& text):
	Widget(width, height, Widget::Status::FREE), m_tsize(30), m_text(&text), m_placeholder_string("Insert")
{
	m_callback			= NULL;
	m_filter_callback	= NULL;
	m_tcolor[0] = sf::Color::White;
	m_tcolor[1] = sf::Color(128, 128, 128);
}

void Textbox::handleInput()
{
}

void Textbox::handleEvent(const sf::Event& e, const sf::RenderWindow& window)
{
	sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	Widget::updateStatus(e, mousePos);

	if (m_toggled)
	{
		if (e.type == sf::Event::TextEntered)
		{
			unsigned char key = e.text.unicode;
			
			if (key == 8) // Backspace
			{
				if (!m_text->empty()) m_text->pop_back();
			}
			else if (key == 13) // Enter
			{
				if (m_callback != NULL) m_callback(*this);
			}
			else if (m_filter_callback == NULL) // Default Filter function
			{
				if (isValid(key)) m_text->push_back(key);
			}
			else if (m_filter_callback(*this, key)) // User-defined Filter function
			{
				m_text->push_back(key);
			}
		}
	}
}

bool Textbox::isValid(const unsigned char& key) const
{
	return (key >= 48 && key <= 57) || (key >= 65 && key <= 90) || (key >= 97 && key <= 122) || (key == 32 || key == 46);
}

void Textbox::update(float dt)
{
}

void Textbox::draw(sf::RenderTarget& rt, sf::RenderStates rs) const
{
	sf::RectangleShape rect(sf::Vector2f((float)m_width, (float)m_height));
	rect.setFillColor((m_toggled) ? m_fcolors[Widget::Status::TOGGLED - 1] : m_fcolors[m_status - 1]);
	rect.setOutlineColor((m_toggled) ? m_bcolors[Widget::Status::TOGGLED - 1] : m_bcolors[m_status - 1]);
	rect.setOutlineThickness((float) m_bsize);

	sf::Text text((m_text->empty()) ? m_placeholder_string : *m_text, ResourceHolder::get().fonts.get("default"));
	sf::FloatRect textRect = text.getLocalBounds();
	text.setFillColor(m_tcolor[(m_text->empty()) ? 1 : 0]);
	text.setCharacterSize(m_tsize);
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	text.setPosition(m_width / 2.0f, m_height / 2.0f);

	rs.texture = NULL;
	rs.transform *= getTransform();
	rt.draw(rect, rs);
	rt.draw(text, rs);
}