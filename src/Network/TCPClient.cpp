#include "TCPClient.h"

bool TCPClient::connect(const std::string& ip, const int& port)
{
	return m_socket.connect(ip, port) == sf::Socket::Status::Done;
	m_socket.setBlocking(false);
}

bool TCPClient::sendMessage(const std::string& msg)
{
	return m_socket.send(msg.data(), msg.size()) == sf::Socket::Status::Done;
}

const std::string& TCPClient::readMessage()
{
	char msg[1024];
	size_t received;
	m_socket.receive(msg, 1024, received);
	return std::string(msg, received);
}