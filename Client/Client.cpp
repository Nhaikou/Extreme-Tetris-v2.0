#include "Client.h"


Client::Client(StateMachine* sm)
{
	stateMachine = sm;
}


Client::~Client()
{
}

void Client::onInitialize()
{
	connectToServer();

	packet >> playerCount;
}

void Client::handleInput()
{
	if (stateMachine->event.type == sf::Event::KeyPressed)
	{
		packet.clear();
		packet << stateMachine->event.key.code;
		server.send(packet);
	}
}

void Client::update(const float dt)
{
	packet.clear();
	server.receive(packet);
	if (packet.getDataSize() == 0)
	{
		return;
	}

	unsigned secretCode;
	packet >> secretCode;

	if (secretCode == 0)
	{
		gameMode = 1;
		sf::Vector2u size;
		sf::Vector2u spawn;
		packet >> size.x >> size.y >> spawn.x >> spawn.y;

		for (int i = 0; i < playerCount; ++i)
		{
			bool lastPlayer = false;
			if (i == playerCount - 1)
			{
				lastPlayer = true;
			}
			sf::Vector2i position;
			packet >> position.x >> position.y;
			Player *player = new Player(size, position, spawn, lastPlayer);
			players.push_back(player);
		}
		sf::View newView(sf::FloatRect(0, 0, players[players.size() - 1]->board->walls[players[players.size() - 1]->board->walls.size() - 1].getPosition().x + 16, players[players.size() - 1]->board->walls[players[players.size() - 1]->board->walls.size() - 1].getPosition().y + 16));
		stateMachine->window.setView(newView);
		stateMachine->window.setSize(sf::Vector2u(players[players.size() - 1]->board->walls[players[players.size() - 1]->board->walls.size() - 1].getPosition()) + sf::Vector2u(16,16));
	}
	else if (secretCode == 1)
	{
		gameMode = 2;
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
			Player *player = new Player(size, sf::Vector2i(i * (size.x + 1) * 16 + 16, -2 * 16), spawn, lastPlayer);
			players.push_back(player);
		}

		sf::View newView(sf::FloatRect(0, 0, players[players.size() - 1]->board->walls[players[players.size() - 1]->board->walls.size() - 1].getPosition().x + 16, players[players.size() - 1]->board->walls[players[players.size() - 1]->board->walls.size() - 1].getPosition().y + 16));
		stateMachine->window.setView(newView);
		stateMachine->window.setSize(sf::Vector2u(players[players.size() - 1]->board->walls[players[players.size() - 1]->board->walls.size() - 1].getPosition()) + sf::Vector2u(16, 16));
	}
	else
	{
		unsigned type, id, i, j;
		packet >> id;
		if (gameMode == 2)
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
			else if(id > clientNumber)
			{
				id = 2;
			}
		}

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
		}
	}
}

void Client::draw(const float dt)
{
	for (int k = 0; k < players.size(); ++k)
	{
		for (int j = 0; j < players[k]->board->getSize().y; ++j)
		{
			for (int i = 0; i < players[k]->board->getSize().x; ++i)
			{
				stateMachine->window.draw(players[k]->board->grid[i][j]);
			}
		}
	}
	for (int j = 0; j < players.size(); ++j)
	{
		for (int i = 0; i < players[j]->board->walls.size(); ++i)
		{
			stateMachine->window.draw(players[j]->board->walls[i]);
		}
	}
}

void Client::connectToServer()
{
	ip = sf::IpAddress::getLocalAddress();

	server.connect(ip, 55001);

	std::cout << "Waiting for an answer from server...";
	server.receive(packet);

	std::cout << "Continue";
	server.setBlocking(false);
}