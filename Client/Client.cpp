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

	blockTex.loadFromFile("../Assets/Block.png");
	block.setTexture(blockTex);
	emptyTex.create(blockTex.getSize().x, blockTex.getSize().y); // Create an empty texture that is the same size as Block.png
	block.setTexture(emptyTex);

	board = new Board();
	board->grid.resize(10);
	for (int i = 0; i < 10; ++i)
	{
		board->grid[i].resize(20);
	}

	for (int j = 0; j < 20; ++j)
	{
		for (int i = 0; i < 10; ++i)
		{
			board->grid[i][j] = block;
			board->grid[i][j].setPosition(block.getGlobalBounds().width * i, block.getGlobalBounds().height * j);
		}
	}
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

	unsigned number;
	for (int j = 0; j < 20; ++j)
	{
		for (int i = 0; i < 10; ++i)
		{
			packet >> number;
			if (number == 0)
			{
				board->grid[i][j].setTexture(emptyTex);
			}
			else
			{
				board->grid[i][j].setTexture(blockTex);
				if (number == 1)
				{
					board->grid[i][j].setColor(sf::Color::Cyan);
				}
				else if (number == 2)
				{
					board->grid[i][j].setColor(sf::Color::Yellow);
				}
				else if (number == 3)
				{
					board->grid[i][j].setColor(sf::Color::Red);
				}
				else if (number == 4)
				{
					board->grid[i][j].setColor(sf::Color::Green);
				}
				else if (number == 5)
				{
					board->grid[i][j].setColor(sf::Color(255, 130, 0));
				}
				else if (number == 6)
				{
					board->grid[i][j].setColor(sf::Color::Blue);
				}
				else if (number == 7)
				{
					board->grid[i][j].setColor(sf::Color::Magenta);
				}
			}
		}
	}
}

void Client::draw(const float dt)
{
	for (int j = 0; j < 20; ++j)
	{
		for (int i = 0; i < 10; ++i)
		{
			stateMachine->window.draw(board->grid[i][j]);
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