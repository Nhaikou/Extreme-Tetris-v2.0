#include "Server.h"


Server::Server()
{
	findPlayers();
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
	int key;
	clients[id]->receive(packet);
	if (packet.getDataSize() == 0)
	{
		return -1;
	}
	packet >> key;
	return key;
}

void Server::sendBoard(unsigned id, bool factory)
{
	packet.clear();
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

	if (!factory)
	{
		for (int i = 0; i < clients.size(); ++i)
		{
			clients[i]->send(packet);
		}
	}
	else
	{
		if (id > 0)
		{
			clients[id - 1]->send(packet);
		}
		else
		{
			clients[clients.size() - 1]->send(packet);
		}

		clients[id]->send(packet);

		if (id < clients.size() - 1)
		{
			clients[id + 1]->send(packet);
		}
		else
		{
			clients[0]->send(packet);
		}
	}
}

void Server::sendState(bool factory)
{
	packet.clear();
	packet << factory;
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
		for (int i = 0; i < players.size(); ++i)
		{
			players[i]->board->updatedGrid = players[i]->board->grid;
		}
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
			unsigned counter = 0;
			if (counter = players[i]->board->clearRow())
			{
				for (int j = 0; j < counter; ++j)
				{
					for (int k = players[i]->currentBlock->positions.size() - 1; k >= 0; --k)
					{
						players[i]->board->grid[players[i]->currentBlock->positions[k].x][players[i]->currentBlock->positions[k].y + j + 1] = BlockType::EMPTY;
						players[i]->board->grid[players[i]->currentBlock->positions[k].x][players[i]->currentBlock->positions[k].y] = players[i]->currentBlock->getType();
					}
				}
			}
			sendBoard(i, true);
		}
	}
}

void Server::standardInitialize()
{
	packet.clear();
	packet << players[0]->board->getSize().x << players[0]->board->getSize().y << players[0]->board->getSpawnPoint().x << players[0]->board->getSpawnPoint().y;

	for (int i = 0; i < clients.size(); ++i)
	{
		packet << players[i]->board->getPosition().x << players[i]->board->getPosition().y;
	}

	for (int i = 0; i < clients.size(); ++i)
	{
		clients[i]->send(packet);
	}
}

void Server::factoryInitialize()
{
	for (int i = 0; i < clients.size(); ++i)
	{
		packet.clear();
		packet << i;
		packet << players[0]->board->getSize().x << players[0]->board->getSize().y << players[0]->board->getSpawnPoint().x << players[0]->board->getSpawnPoint().y;
		clients[i]->send(packet);
	}
}

void Server::moveLineLeft()
{

}

void Server::moveLineRight()
{
	std::vector<std::vector<unsigned>> tempSlices;
	for (int i = 0; i < players.size(); ++i)
	{
		std::vector<unsigned> tempSlice = players[i]->board->gridSlice;
		tempSlices.push_back(tempSlice);
	}

	for (int k = 0; k < players.size(); ++k)
	{
		for (int i = 0; i < players[k]->currentBlock->positions.size(); ++i)
		{
			players[k]->board->grid[players[k]->currentBlock->positions[i].x][players[k]->currentBlock->positions[i].y] = BlockType::EMPTY;
		}

		for (int j = 0; j < players[k]->board->getSize().y; ++j)
		{
			for (int i = players[k]->board->getSize().x - 1; i >= 0; --i)
			{
				if (i == players[k]->board->getSize().x - 1)
				{
					players[k]->board->gridSlice[j] = players[k]->board->grid[i][j];
				}
				if (i == 0)
				{
					if (k == 0 && players.size() != 1)
					{
						players[k]->board->grid[i][j] = players[players.size() - 1]->board->gridSlice[j];
					}
					else if (k == 0 && players.size() == 1)
					{
						players[k]->board->grid[i][j] = tempSlices[k][j];
					}
					else
					{
						players[k]->board->grid[i][j] = tempSlices[k - 1][j];
					}
				}
				else
				{
					players[k]->board->grid[i][j] = players[k]->board->grid[i - 1][j];
				}
			}
		}

		bool moveBlock = false, blockWrapped = false;
		for (int i = 0; i < players[k]->currentBlock->positions.size(); ++i)
		{
			if (players[k]->board->grid[players[k]->currentBlock->positions[i].x][players[k]->currentBlock->positions[i].y] != BlockType::EMPTY)
			{
				moveBlock = true;
			}
		}

		if (moveBlock)
		{
			for (int i = 0; i < players[k]->currentBlock->positions.size(); ++i)
			{
				players[k]->currentBlock->positions[i].x++;
				if (players[k]->currentBlock->positions[i].x >= players[k]->board->getSize().x)
				{
					blockWrapped = true;
				}
			}
		}
		if (blockWrapped)
		{
			unsigned dropCount = 0, currentDropCount = players[k]->board->getSize().y;
			for (int i = 0; i < players[k]->currentBlock->positions.size(); ++i)
			{
				dropCount = 0;
				if (players[k]->currentBlock->positions[i].x >= players[k]->board->getSize().x)
				{
					while (players[k]->currentBlock->positions[i].y + dropCount != players[k]->board->getSize().y - 1 && players[k]->board->gridSlice[players[k]->currentBlock->positions[i].y + dropCount + 1] == BlockType::EMPTY)
					{
						dropCount++;
					}
				}
				else
				{
					while (players[k]->currentBlock->positions[i].y + dropCount != players[k]->board->getSize().y - 1 && players[k]->board->grid[players[k]->currentBlock->positions[i].x][players[k]->currentBlock->positions[i].y + dropCount + 1] == BlockType::EMPTY)
					{
						dropCount++;
					}
				}
				if (dropCount < currentDropCount)
				{
					currentDropCount = dropCount;
				}
			}

			for (int i = 0; i < players[k]->currentBlock->positions.size(); ++i)
			{
				for (int j = 0; j < currentDropCount; ++j)
				{
					if (players[k]->currentBlock->positions[i].x >= players[k]->board->getSize().x)
					{
						players[k]->board->gridSlice[players[k]->currentBlock->positions[i].y + currentDropCount] = players[k]->currentBlock->getType();
					}
					else
					{
						players[k]->board->grid[players[k]->currentBlock->positions[i].x][players[k]->currentBlock->positions[i].y + currentDropCount] = players[k]->currentBlock->getType();
					}
				}
			}

			players[k]->spawnBlock();
		}
		else
		{
			for (int i = 0; i < players[k]->currentBlock->positions.size(); ++i)
			{
				players[k]->board->grid[players[k]->currentBlock->positions[i].x][players[k]->currentBlock->positions[i].y] = players[k]->currentBlock->getType();
			}
		}
	}
}