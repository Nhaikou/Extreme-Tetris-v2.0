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
		sf::Vector2u size;
		sf::Vector2u spawn;
		packet >> size.x >> size.y >> spawn.x >> spawn.y;

		for (int i = 0; i < playerCount; ++i)
		{
			sf::Vector2i position;
			packet >> position.x >> position.y;
			Player *player = new Player(size, position, spawn);
			players.push_back(player);
			std::cout << "Player added" << std::endl;
		}
	}
	else
	{
		unsigned type, id;
		packet >> id;
		for (int j = 0; j < players[id]->board->getSize().y; ++j)
		{
			for (int i = 0; i < players[id]->board->getSize().x; ++i)
			{
				packet >> type;
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