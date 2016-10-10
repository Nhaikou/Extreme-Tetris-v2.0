#ifndef NETWORK_H
#define NETWORK_H

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "Board.h"
#include <iostream>

class Network
{
public:
	Network();
	~Network();

	void sendBoard(Board *board); // Sends the updated board to server which then forwards it to all players who need the info
	void sendScore(); // Sends the player's score to server which then forwards it to other players

	void receiveBoard(Board *leftBoard, Board *rightBoard); // Factory Tetris only, receives an updated board from an adjacent player and updates the board next to this client accordingly
	void receiveScore(); // Receive an updated score from another player and update scores accordingly

private:
	sf::IpAddress ip;
	sf::TcpSocket socket;
	sf::Packet packet; // Contains the variables that are sent between client and server
	unsigned playerNumber; // Client's number that the server keeps track of
};

#endif