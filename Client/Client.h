#ifndef CLIENT_H
#define CLIENT_H

#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Player.h"
#include <iostream>

enum PacketType
{
	BOARD = 0,
	BOARDSLICE = 1,
	NEXTBLOCK = 2,
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
	void receive();
	void receiveBoard();
	void receiveBoardSlice();
	void receiveNextBlock();
	bool receiveState();

	sf::IpAddress ip;
	sf::TcpSocket server;
	sf::Packet packet;

	unsigned playerCount, clientNumber;
	bool gameMode, updateAnimations = false;
	std::vector<Player*> players;
};
#endif;