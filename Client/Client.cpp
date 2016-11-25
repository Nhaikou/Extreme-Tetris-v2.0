#include "Client.h"


Client::Client()
{
	connectToServer();
}


Client::~Client()
{
	for (int i = 0; i < players.size(); ++i)
	{
		delete players[i];
	}
}

void Client::sendInput(int key)
{
	packet.clear();
	packet << key;
	server.send(packet);
}

void Client::connectToServer()
{
	ip = sf::IpAddress::getLocalAddress();
	//ip = "172.31.16.142";
	server.connect(ip, 55002);

	std::cout << "Waiting for an answer from server...";
	server.receive(packet);
	packet >> playerCount;

	std::cout << "\nVote for gamemode! S (=Standard) or F (=Factory)" << std::endl;
	server.setBlocking(false);
}

void Client::standardInitialize()
{
	while (true)
	{
		packet.clear();
		server.receive(packet);
		if (!packet.getDataSize() == 0)
		{
			break;
		}
	}

	sf::Vector2u size;
	sf::Vector2u spawn;
	packet >> clientNumber >> size.x >> size.y >> spawn.x >> spawn.y;

	for (int i = 0; i < playerCount; ++i)
	{
		bool lastPlayer = false;
		if (i == playerCount - 1)
		{
			lastPlayer = true;
		}

		Player *player = new Player(size, spawn, i, gameMode);
		players.push_back(player);
	}
}

void Client::factoryInitialize()
{
	while (true)
	{
		packet.clear();
		server.receive(packet);
		if (!packet.getDataSize() == 0)
		{
			break;
		}
	}

	sf::Vector2u size;
	sf::Vector2u spawn;
	packet >> clientNumber >> size.x >> size.y >> spawn.x >> spawn.y;
	for (int i = 0; i < 3; ++i)
	{
		bool lastPlayer = false;
		if (i == 2)
		{
			lastPlayer = true;
		}
		Player *player = new Player(size, spawn, i, gameMode);
		players.push_back(player);
	}
}

void Client::receive()
{
	packet.clear();
	server.receive(packet);
	if (packet.getDataSize() == 0)
	{
		return;
	}

	unsigned packetType;
	packet >> packetType;

	if (packetType == BOARD)
	{
		receiveBoard();
	}
	else if (packetType == BOARDSLICE)
	{
		receiveBoardSlice();
	}
	else if (packetType == NEXTBLOCK)
	{
		receiveNextBlock();
	}
	else if(packetType == SCORE)
	{
		receiveScore();
	}
}

void Client::receiveBoard()
{
	unsigned type, id, i, j, packetType;
	packet >> id;

	id = idFix(id);

	while (!packet.endOfPacket())
	{
		packet >> i >> j >> type;
		if (type == BlockType::EMPTY)
		{
			players[id]->board->grid[i][j].setTexture(players[id]->board->emptyTex);
			players[id]->board->grid[i][j].setColor(sf::Color::White);
		}
		else
		{
			players[id]->board->grid[i][j].setTexture(players[id]->board->blockTex);
			if (type == BlockType::BLOCKI)
			{
				players[id]->board->grid[i][j].setColor(sf::Color::Cyan);
			}
			else if (type == BlockType::BLOCKO)
			{
				players[id]->board->grid[i][j].setColor(sf::Color::Yellow);
			}
			else if (type == BlockType::BLOCKZ)
			{
				players[id]->board->grid[i][j].setColor(sf::Color::Red);
			}
			else if (type == BlockType::BLOCKS)
			{
				players[id]->board->grid[i][j].setColor(sf::Color::Green);
			}
			else if (type == BlockType::BLOCKL)
			{
				players[id]->board->grid[i][j].setColor(sf::Color(255, 130, 0));
			}
			else if (type == BlockType::BLOCKJ)
			{
				players[id]->board->grid[i][j].setColor(sf::Color::Blue);
			}
			else if (type == BlockType::BLOCKT)
			{
				players[id]->board->grid[i][j].setColor(sf::Color::Magenta);
			}
		}

		if (gameMode && playerCount == 1)
		{
			players[id - 1]->board->grid[i][j].setTexture(*players[id]->board->grid[i][j].getTexture());
			players[id - 1]->board->grid[i][j].setColor(players[id]->board->grid[i][j].getColor());
			players[id + 1]->board->grid[i][j].setTexture(*players[id]->board->grid[i][j].getTexture());
			players[id + 1]->board->grid[i][j].setColor(players[id]->board->grid[i][j].getColor());
		}
		if (gameMode && playerCount == 2)
		{
			if (clientNumber == 0)
			{
				players[2]->board->grid[i][j].setTexture(*players[0]->board->grid[i][j].getTexture());
				players[2]->board->grid[i][j].setColor(players[0]->board->grid[i][j].getColor());
			}
			else
			{
				players[0]->board->grid[i][j].setTexture(*players[2]->board->grid[i][j].getTexture());
				players[0]->board->grid[i][j].setColor(players[2]->board->grid[i][j].getColor());
			}
		}
	}
}

void Client::receiveBoardSlice()
{
	unsigned type, id, i;
	packet >> id;

	if (id == clientNumber)
	{
		id = 1;
	}
	else if (clientNumber == playerCount - 1 && id == 0)
	{
		id = 2;
	}
	else if (clientNumber == 0 && id == playerCount - 1)
	{
		id = 0;
	}
	else if (id < clientNumber)
	{
		id = 0;
	}
	else if (id > clientNumber)
	{
		id = 2;
	}

	while (!packet.endOfPacket())
	{
		packet >> i >> type;
		if (type == BlockType::EMPTY)
		{
			players[id]->board->gridSlice[i].setTexture(players[id]->board->emptyTex);
			players[id]->board->gridSlice[i].setColor(sf::Color::White);
		}
		else
		{
			players[id]->board->gridSlice[i].setTexture(players[id]->board->blockTex);
			if (type == BlockType::BLOCKI)
			{
				players[id]->board->gridSlice[i].setColor(sf::Color::Cyan);
			}
			else if (type == BlockType::BLOCKO)
			{
				players[id]->board->gridSlice[i].setColor(sf::Color::Yellow);
			}
			else if (type == BlockType::BLOCKZ)
			{
				players[id]->board->gridSlice[i].setColor(sf::Color::Red);
			}
			else if (type == BlockType::BLOCKS)
			{
				players[id]->board->gridSlice[i].setColor(sf::Color::Green);
			}
			else if (type == BlockType::BLOCKL)
			{
				players[id]->board->gridSlice[i].setColor(sf::Color(255, 130, 0));
			}
			else if (type == BlockType::BLOCKJ)
			{
				players[id]->board->gridSlice[i].setColor(sf::Color::Blue);
			}
			else if (type == BlockType::BLOCKT)
			{
				players[id]->board->gridSlice[i].setColor(sf::Color::Magenta);
			}
		}

		if (gameMode && playerCount == 1)
		{
			players[id - 1]->board->gridSlice[i].setTexture(*players[id]->board->gridSlice[i].getTexture());
			players[id - 1]->board->gridSlice[i].setColor(players[id]->board->gridSlice[i].getColor());
			players[id + 1]->board->gridSlice[i].setTexture(*players[id]->board->gridSlice[i].getTexture());
			players[id + 1]->board->gridSlice[i].setColor(players[id]->board->gridSlice[i].getColor());
		}
		if (gameMode && playerCount == 2 && clientNumber != 0)
		{
			players[0]->board->gridSlice[i].setTexture(*players[2]->board->gridSlice[i].getTexture());
			players[0]->board->gridSlice[i].setColor(players[2]->board->gridSlice[i].getColor());
		}
	}
}

void Client::receiveNextBlock()
{
	unsigned id, type;
	packet >> id >> type;

	id = idFix(id);

	players[id]->updateNextBlock(type);
}

void Client::receiveScore()
{
	unsigned id, score;
	packet >> id >> score;

	id = idFix(id);

	players[id]->score = score;
}

bool Client::receiveState()
{
	server.receive(packet);
	if (packet.getDataSize() == 0)
	{
		return false;
	}
	packet >> gameMode;

	return true;
}

unsigned Client::idFix(unsigned id)
{
	if (gameMode)
	{
		if (id == clientNumber)
		{
			id = 1;
		}
		else if (clientNumber == playerCount - 1 && id == 0)
		{
			id = 2;
		}
		else if (clientNumber == 0 && id == playerCount - 1)
		{
			id = 0;
		}
		else if (id < clientNumber)
		{
			id = 0;
		}
		else if (id > clientNumber)
		{
			id = 2;
		}
	}
	else
	{
		if (id == clientNumber)
		{
			id = 0;
		}
		else if (id < clientNumber)
		{
			id++;
		}
	}

	return id;
}