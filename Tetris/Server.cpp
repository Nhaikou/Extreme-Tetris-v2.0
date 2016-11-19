#include "Server.h"


Server::Server(bool multiplayer)
{
	networking = false;
	if (multiplayer)
	{
		findPlayers();
		networking = true;
	}
	lineTime.y = 2000;
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
				packet << i << j << players[id]->board->grid[i][j];
			}
		}
	}
	for (int i = 0; i < clients.size(); ++i)
	{
		clients[i]->send(packet);
	}
}

void Server::updateLine(const float dt)
{
	lineTime.x += dt;
	if (lineTime.x >= lineTime.y)
	{
		lineTime.x = 0;
		if (lineDirection == -1)
		{
			moveLineLeft();
		}
		else
		{
			moveLineRight();
		}
		for (int i = 0; i < players.size(); ++i)
		{
			sendBoard(i);
		}
		std::cout << "Line moved." << std::endl;
	}
}

/*
void Server::moveLineLeft()
{
	bool hitCurrentBlock = false;

	for (int k = 0; k < players.size(); ++k)
	{
		for (int j = 0; j < players[k]->board->getSize().y; ++j)
		{
			for (int i = 0; i < players[k]->board->getSize().x; ++i)
			{
				players[k]->board->updatedGrid[i][j] = BlockType::EMPTY;
			}
		}
	}

	for (int k = 0; k < players.size(); ++k)
	{
		for (int j = 0; j < players[k]->board->getSize().y; ++j)
		{
			for (int i = 0; i < players[k]->board->getSize().x; ++i)
			{
				if (!(players[k]->currentBlock->positions[0] == sf::Vector2i(i, j) || players[k]->currentBlock->positions[1] == sf::Vector2i(i, j) ||
					players[k]->currentBlock->positions[2] == sf::Vector2i(i, j) || players[k]->currentBlock->positions[3] == sf::Vector2i(i, j)))
				{
					if (players[k]->board->grid[i][j] == BlockType::EMPTY)
					{
						if (i == 0)
						{
							if (players[k]->currentBlock->positions[0] == sf::Vector2i(players[k]->board->getSize().x - 1, j) || players[k]->currentBlock->positions[1] == sf::Vector2i(players[k]->board->getSize().x - 1, j) ||
								players[k]->currentBlock->positions[2] == sf::Vector2i(players[k]->board->getSize().x - 1, j) || players[k]->currentBlock->positions[3] == sf::Vector2i(players[k]->board->getSize().x - 1, j))
							{
								hitCurrentBlock = true;
							}
							players[k]->board->updatedGrid[players[k]->board->getSize().x - 1][j] = players[k]->board->grid[i][j];
						}
						else
						{
							if (players[k]->currentBlock->positions[0] == sf::Vector2i(i - 1, j) || players[k]->currentBlock->positions[1] == sf::Vector2i(i - 1, j) ||
								players[k]->currentBlock->positions[2] == sf::Vector2i(i - 1, j) || players[k]->currentBlock->positions[3] == sf::Vector2i(i - 1, j))
							{
								hitCurrentBlock = true;
							}
							players[k]->board->updatedGrid[i - 1][j] = players[k]->board->grid[i][j];
						}
					}
				}
			}
		}
	}

	if (hitCurrentBlock)
	{
		bool blockWrapped = false;
		for (int j = 0; j < players.size(); ++j)
		{
			for (int i = 0; i < players[j]->currentBlock->tetra; ++i)
			{
				players[j]->currentBlock->positions[i].x--;
				if (players[j]->currentBlock->positions[i].x == -1)
				{
					players[j]->currentBlock->positions[i].x = players[j]->board->getSize().x - 1;
					blockWrapped = true;
				}
				players[j]->board->updatedGrid[players[j]->currentBlock->positions[i].x][players[j]->currentBlock->positions[i].y] = players[j]->currentBlock->getType();
			}
		}
		for (int i = 0; i < players.size(); ++i)
		{
			players[i]->board->grid = players[i]->board->updatedGrid;
			if (blockWrapped)
			{
				while (true)
				{
					if (!players[i]->currentBlock->moveDown())
					{

						return;
					}
				}
			}
		}
	}
	else
	{
		for (int j = 0; j < players.size(); ++j)
		{
			for (int i = 0; i < players[j]->currentBlock->tetra; ++i)
			{
				players[j]->board->updatedGrid[players[j]->currentBlock->positions[i].x][players[j]->currentBlock->positions[i].y] = players[j]->currentBlock->getType();
			}
			players[j]->board->grid = players[j]->board->updatedGrid;
		}
	}
}
*/

void Server::moveLineLeft()
{

}

void Server::moveLineRight()
{
	std::vector<unsigned> tempSlice = players[players.size() - 1]->board->gridSlice;

	for (int k = players.size() - 1; k >= 0; --k)
	{
		for (int j = 0; j < players[k]->board->getSize().y; ++j)
		{
			for (int i = players[k]->board->getSize().x - 1; i >= 0; --i)
			{
				if (i == players[k]->board->getSize().x - 1)
				{
					players[k]->board->gridSlice[j] = players[k]->board->grid[i][j];
				}
				else if (i == 0)
				{
					if (k - 1 > 0)
					{
						players[k]->board->updatedGrid[i][j] = players[k - 1]->board->gridSlice[j];
					}
					else
					{
						players[k]->board->updatedGrid[i][j] = players[players.size() - 1]->board->gridSlice[j];
					}			
				}
				else
				{
					players[k]->board->updatedGrid[i + 1][j] = players[k]->board->grid[i][j];
				}
			}
		}
	}

	for (int i = 0; i < players[0]->board->getSize().y; ++i)
	{
		players[0]->board->updatedGrid[0][i] = tempSlice[i];
	}
	for (int i = 0; i < players.size(); ++i)
	{
		players[i]->board->grid = players[i]->board->updatedGrid;
	}
}