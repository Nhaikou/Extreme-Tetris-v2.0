#ifndef SERVER_H
#define SERVER_H

#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include <iostream>
#include <vector>

enum PacketType
{
	GRID = 0,
	GRIDSLICE = 1,
	NEXTBLOCK = 2,
	SCORE = 3,
};

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
	void sendBoard(unsigned id);
	void sendBoardSlice(unsigned id);
	void sendNextBlock(unsigned id);
	void sendScore(unsigned id);
	void sendState(bool factory);

	void sendToGameMode(unsigned id);

	void updateLine(const float dt);
	void moveLineLeft();
	void moveLineRight();
	void newBag();

	void gameModeInitialize(bool factory);

	std::vector<sf::TcpSocket*> clients;
	std::vector<unsigned> bags;

private:
	unsigned blockTypeCount = 7;
	bool searchPlayers = true, factoryMode = false;
	char answer;

	sf::Vector2f lineTime = { 0, 0 };
	int lineDirection = 1;
};
#endif;

