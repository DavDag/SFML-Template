#include "Server.h"

#include <iostream>

bool Server::bind(const std::string& ip, const int& port)
{
	if (m_listener.listen(port) != sf::Socket::Status::Done) return false;
	m_ip = ip;
	return true;
}

bool Server::waitUser()
{
	sf::TcpSocket* tcpsocket = new sf::TcpSocket;
	if (m_listener.accept(*tcpsocket) != sf::Socket::Status::Done) return false;
	tcpsocket->setBlocking(false);
	m_clients.push_back(tcpsocket);
	return true;
}

bool Server::sendMessage(const std::string& msg)
{
	for (int i = 0; i < m_clients.size(); ++i)
		if (m_clients[i]->send(msg.data(), msg.size()) != sf::Socket::Status::Done)
			return false;
	return true;
}

const std::string Server::readMessage(int player)
{
	char msg[1024];
	size_t received;
	m_clients[player]->receive(msg, 1024, received);
	std::string data(msg, received);
	return data;
}