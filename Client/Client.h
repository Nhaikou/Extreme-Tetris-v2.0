#ifndef CLIENT_H
#define CLIENT_H

#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Player.h"
#include <iostream>

#include <sstream>

enum PacketType
{
	BOARD = 0,
	BOARDSLICE = 1,
	NEXTBLOCK = 2,
	SCORE = 3,
};

class Client
{
public:
	Client(std::string name, std::string ipAddress);
	~Client();

	void connectToServer();

	void sendInput(int key);

	void standardInitialize();
	void factoryInitialize();
	void receive();
	void receiveBoard();
	void receiveBoardSlice();
	void receiveNextBlock();
	void receiveScore();
	void receiveNames();
	bool receiveState();

	unsigned idFix(unsigned id);

	sf::IpAddress ip;
	sf::TcpSocket server;
	sf::Packet packet;

	unsigned playerCount, clientNumber;
	bool gameMode, connectionFail = false;
	std::vector<Player*> players;
	std::string playerName;
	std::vector<std::string> playerNames;
};
#endif;