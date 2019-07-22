#pragma once

#include <string>
#include <vector>

#include <SFML/Network.hpp>

class Server
{
	public:
		Server() { m_ip = ""; }

		bool bind(const std::string&, const int&);
		bool waitUser();
		bool sendMessage(const std::string&);
		const std::string readMessage(int player);

		int getNumUsers() const { return m_clients.size(); }

	private:
		std::string m_ip;
		sf::TcpListener m_listener;
		std::vector<sf::TcpSocket*> m_clients;
};