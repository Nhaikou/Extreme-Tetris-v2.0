#ifndef SERVER_H
#define SERVER_H

#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include <iostream>
#include <vector>

class Server
{
public:
	Server();
	~Server();

	sf::SocketSelector socketSelector;
	sf::TcpSocket tcpSocket;
	sf::TcpListener tcpListener;
	sf::Packet packet;

	std::vector<Player*> players;
	void findPlayers();
	int receiveButtonPress(unsigned id);
	void sendBoard(unsigned id, bool factory);
	void sendState(bool factory);
	void updateLine(const float dt);
	void moveLineLeft();
	void moveLineRight();

	void standardInitialize();
	void factoryInitialize();

	std::vector<sf::TcpSocket*> clients;

private:
	bool searchPlayers = true;
	char answer;

	sf::Vector2f lineTime = { 0, 0 };
	int lineDirection = 1;
};
#endif;

