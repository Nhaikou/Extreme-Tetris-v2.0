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
					Player *player = new Player();
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
	for (int j = 0; j < players[id]->board->getSize().y; ++j)
	{
		for (int i = 0; i < players[id]->board->getSize().x; ++i)
		{
			if (players[id]->board->grid[i][j].getTexture() == &players[id]->board->emptyTex)
			{
				packet << 0;
			}
			else if (players[id]->board->grid[i][j].getColor() == sf::Color::Cyan)
			{
				packet << 1;
			}
			else if (players[id]->board->grid[i][j].getColor() == sf::Color::Yellow)
			{
				packet << 2;
			}
			else if (players[id]->board->grid[i][j].getColor() == sf::Color::Red)
			{
				packet << 3;
			}
			else if (players[id]->board->grid[i][j].getColor() == sf::Color::Green)
			{
				packet << 4;
			}
			else if (players[id]->board->grid[i][j].getColor() == sf::Color(255, 130, 0))
			{
				packet << 5;
			}
			else if (players[id]->board->grid[i][j].getColor() == sf::Color::Blue)
			{
				packet << 6;
			}
			else if (players[id]->board->grid[i][j].getColor() == sf::Color::Magenta)
			{
				packet << 7;
			}
		}
	}
	clients[id]->send(packet);
}