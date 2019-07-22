#pragma once

#include <string>
#include <functional>

#include "../States/BaseState.h"
#include "Widget.h"

class Button: public Widget
{
	public:
		Button(int, int, const std::string&);

		void handleInput() override;
		void handleEvent(const sf::Event&, const sf::RenderWindow&) override;
		void update(float) override;
		void draw(sf::RenderTarget&, sf::RenderStates) const override;

		void setCallback(std::function<void(Button&)> callback) { m_callback = callback; }
		void setTextSize(int size) { m_tsize = size; }
		void setTextColor(sf::Color c) { m_tcolor = c; }

	private:
		int m_tsize;
		sf::Color m_tcolor;
		std::string m_text;
		std::function<void(Button&)> m_callback;
};