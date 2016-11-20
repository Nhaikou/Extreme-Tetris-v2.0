#ifndef SERVER_H
#define SERVER_H

#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include <iostream>
#include <vector>

enum Networking
{
	SINGLEPLAYER = false,
	MULTIPLAYER = true,
};

enum GameMode
{
	MENU = 0,
	STANDARD = 1,
	FACTORY = 2,
};

class Server
{
public:
	Server(bool multiplayer);
	~Server();

	sf::SocketSelector socketSelector;
	sf::TcpSocket tcpSocket;
	sf::TcpListener tcpListener;
	sf::Packet packet;

	std::vector<Player*> players;
	void findPlayers();
	int receiveButtonPress(unsigned id);
	void sendBoard(unsigned id);
	void updateLine(const float dt);
	void moveLineLeft();
	void moveLineRight();

	std::vector<sf::TcpSocket*> clients;
	bool networking;
	unsigned gameMode;

private:
	bool searchPlayers = true;
	char answer;

	sf::Vector2f lineTime = { 0, 0 };
	int lineDirection = 1;
};
#endif;

