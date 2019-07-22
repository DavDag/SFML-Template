#pragma once

#include <string>
#include <functional>

#include "Widget.h"

class Textbox: public Widget
{
	public:
		Textbox(int, int, std::string&);

		void handleInput() override;
		void handleEvent(const sf::Event&, const sf::RenderWindow&) override;
		void update(float) override;
		void draw(sf::RenderTarget&, sf::RenderStates) const override;

		bool isValid(const unsigned char&) const;
		void setCallback(std::function<void(Textbox&)> callback) { m_callback = callback; }
		void setFilterCallback(std::function<bool(Textbox&, unsigned char&)> callback) { m_filter_callback = callback; }

		void setPlaceholderString(const std::string& text) { m_placeholder_string = text; }
		std::string getString() const { return *m_text; }
		void clearString() { m_text->clear(); }

		void setTextSize(int size) { m_tsize = size; }
		void setTextColor(sf::Color c) { m_tcolor[0] = c; }
		void setPlaceHolderTextColor(sf::Color c) { m_tcolor[1] = c; }

	private:
		int m_tsize;
		sf::Color m_tcolor[2];
		std::string* m_text;
		std::string m_placeholder_string;
		std::function<void(Textbox&)> m_callback;
		std::function<bool(Textbox& , unsigned char&)> m_filter_callback;
};