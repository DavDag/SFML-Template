#pragma once

#include <SFML\Graphics.hpp>

class Widget: public sf::Drawable, public sf::Transformable
{
	public:
		enum Status : unsigned int { FREE = 0x01, HOVER = 0x02, CLICKED = 0x03, TOGGLED = 0x04};

	public:
		virtual void handleInput() = 0;
		virtual void handleEvent(const sf::Event&, const sf::RenderWindow&) = 0;
		virtual void update(float) = 0;
		virtual void draw(sf::RenderTarget&, sf::RenderStates) const override = 0;

		Widget(int width, int height, Status status) :
			m_width(width), m_height(height), m_status(status), m_toggled(false), m_bsize(1)
		{
			m_fcolors[Widget::Status::FREE - 1]		= sf::Color::White;
			m_fcolors[Widget::Status::HOVER - 1]	= sf::Color::Yellow;
			m_fcolors[Widget::Status::CLICKED - 1]	= sf::Color::Red;
			m_fcolors[Widget::Status::TOGGLED - 1]	= sf::Color::Blue;
			m_bcolors[Widget::Status::FREE - 1]		= sf::Color::White;
			m_bcolors[Widget::Status::HOVER - 1]	= sf::Color::Yellow;
			m_bcolors[Widget::Status::CLICKED - 1]	= sf::Color::Red;
			m_bcolors[Widget::Status::TOGGLED - 1]	= sf::Color::Blue;
		}

		void updateStatus(const sf::Event& e, const sf::Vector2f& mousePos)
		{
			if (e.type == sf::Event::MouseButtonPressed)
			{
				if (m_status == Widget::Status::HOVER)	m_status = Widget::Status::CLICKED;
				else									m_status = Widget::Status::FREE;
			}
			else if (e.type == sf::Event::MouseButtonReleased)
			{
				if (m_status == Widget::Status::CLICKED)
				{
					sf::FloatRect bounds = getBounds();
					if (bounds.contains(mousePos))
					{
						m_status = Widget::Status::HOVER;
					}
					else
					{
						m_status = Widget::Status::FREE;
					}

					m_toggled = !m_toggled;
				}
				else
				{
					m_toggled = false;
				}
			}
			else if (e.type == sf::Event::MouseMoved)
			{
				sf::FloatRect bounds = getBounds();
				if (bounds.contains(mousePos))
				{
					m_status = (m_status == Widget::Status::FREE) ? Widget::Status::HOVER : m_status;
				}
				else
				{
					m_status = (m_status == Widget::Status::CLICKED) ? m_status : Widget::Status::FREE;
				}
			}
		}
		sf::FloatRect getBounds() const
		{
			sf::FloatRect rect(sf::Vector2f(0, 0), sf::Vector2f((float)m_width, (float)m_height));
			return getTransform().transformRect(rect);
		}

		void setToggled(bool toggled) { m_toggled = toggled; }
		void setFillColor(sf::Color c, Widget::Status status) { m_fcolors[status - 1] = c; }
		void setBorderColor(sf::Color c, Widget::Status status) { m_bcolors[status - 1] = c; }
		void setBorderSize(int size) { m_bsize = size; }

	protected:
		Status m_status;
		int m_width, m_height;
		bool m_toggled;
		sf::Color m_fcolors[4];
		sf::Color m_bcolors[4];
		int m_bsize;
};