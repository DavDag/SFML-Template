#pragma once

#include <SFML/Network.hpp>

class TCPClient
{
	public:
		TCPClient() { }

		bool connect(const std::string&, const int&);
		bool sendMessage(const std::string&);
		const std::string& readMessage();

	private:
		sf::TcpSocket m_socket;
};