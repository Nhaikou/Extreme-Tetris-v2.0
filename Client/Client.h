#ifndef CLIENT_H
#define CLIENT_H

#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Player.h"
#include <iostream>

enum PacketType
{
	GRID = 0,
	GRIDSLICE = 1,
};

class Client
{
public:
	Client();
	~Client();

	void sendInput(int key);

	void connectToServer();

	void standardInitialize();
	void factoryInitialize();
	void receiveBoard();
	bool receiveState();

	sf::IpAddress ip;
	sf::TcpSocket server;
	sf::Packet packet;

	unsigned playerCount, clientNumber;
	bool gameMode;
	std::vector<Player*> players;
};
#endif;