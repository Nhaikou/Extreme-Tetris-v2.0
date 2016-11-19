#include "Server.h"


Server::Server(bool multiplayer)
{
	networking = false;
	if (multiplayer)
	{
		findPlayers();
		networking = true;
	}
}

Server::~Server()
{
	for (int i = 0; i < clients.size(); ++i)
	{
		delete clients[i];
	}
}

void Server::findPlayers()
{
	tcpListener.listen(55001);
	socketSelector.add(tcpListener);

	while (searchPlayers)
	{
		std::cout << "Waiting for players.." << std::endl;
		if (socketSelector.wait() && searchPlayers)
		{
			if (socketSelector.isReady(tcpListener) && searchPlayers)
			{
				sf::TcpSocket* client = new sf::TcpSocket;
				if (tcpListener.accept(*client) == sf::Socket::Done)
				{
					clients.push_back(client);
					clients[clients.size() - 1]->setBlocking(false);
					socketSelector.add(*client);
					Player *player = new Player(clients.size() - 1, sf::Vector2i(0, -2), sf::Vector2u(10, 20), sf::Vector2u(3, 3));
					players.push_back(player);
				}
				else
				{
					delete client;
				}

				std::cout << "Wait for more players? Y/N";
				std::cin >> answer;
				if (answer == 'n')
				{
					packet << players.size();
					for (int i = 0; i < clients.size(); ++i)
					{
						clients[i]->send(packet);
					}
					searchPlayers = false;
				}
			}
		}
	}
}

int Server::receiveButtonPress(unsigned id)
{
	if (!networking)
	{
		return -1;
	}

	int key;
	clients[id]->receive(packet);
	if (packet.getDataSize() == 0)
	{
		return -1;
	}
	packet >> key;
	return key;
}

void Server::sendBoard(unsigned id)
{
	packet.clear();
	packet << 1; // secretCode
	packet << id;

	for (int j = 0; j < players[id]->board->getSize().y; ++j)
	{
		for (int i = 0; i < players[id]->board->getSize().x; ++i)
		{
			if (players[id]->board->updatedGrid[i][j] != players[id]->board->grid[i][j])
			{
				packet << i << j << players[id]->board->grid[i][j].z;
			}
		}
	}
	for (int i = 0; i < clients.size(); ++i)
	{
		clients[i]->send(packet);
	}
}