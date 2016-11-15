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

	std::vector<sf::TcpSocket*> clients;
	bool networking;

private:
	bool searchPlayers = true;
	char answer;
};
#endif;

