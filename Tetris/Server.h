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
	NAMES = 4,
};

enum WinningCondition
{
	ELIMINATION = 0,
	SCOREATTACK = 1,
	TIMELIMIT = 2,
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
	void sendPlayerNames();
	void sendState(bool factory);

	void sendToGameMode(unsigned id);

	void updateLine(const float dt);
	void moveLineLeft();
	void moveLineRight();
	void newBag();

	void boardFull(unsigned id);
	void endGame();

	void gameModeInitialize(bool factory);

	std::vector<sf::TcpSocket*> clients;
	std::vector<unsigned> bags;

private:
	unsigned blockTypeCount = 7, winningCondition = SCOREATTACK;
	bool searchPlayers = true, factoryMode = false;
	char answer;

	sf::Vector2f lineTime = { 0, 0 };
	int lineDirection = 1;
};
#endif;

