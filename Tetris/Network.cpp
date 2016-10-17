#include "Network.h"


Network::Network()
{
	ip = sf::IpAddress::getLocalAddress();

	socket.connect(ip, 2000);

	std::cout << "Waiting for an answer from server...";
	socket.receive(packet);

	std::cout << "Continue";
	socket.setBlocking(false);
}


Network::~Network()
{
}

void Network::sendBoard(Board *board)
{
	for (int j = 0; j < board->getSize().y; ++j)
	{
		for (int i = 0; i < board->getSize().x; ++i)
		{
			if (board->grid[i][j].getTexture() == &board->emptyTex)
			{
				packet << 0;
			}
			else
			{
				if (board->grid[i][j].getColor() == sf::Color::Cyan)
				{
					packet << 1;
				}
				else if (board->grid[i][j].getColor() == sf::Color::Yellow)
				{
					packet << 2;
				}
				else if (board->grid[i][j].getColor() == sf::Color::Red)
				{
					packet << 3;
				}
				else if (board->grid[i][j].getColor() == sf::Color::Green)
				{
					packet << 4;
				}
				else if (board->grid[i][j].getColor() == sf::Color(255, 130, 0))
				{
					packet << 5;
				}
				else if (board->grid[i][j].getColor() == sf::Color::Blue)
				{
					packet << 6;
				}
				else if (board->grid[i][j].getColor() == sf::Color::Magenta)
				{
					packet << 7;
				}
			}
		}
	}
	socket.send(packet);
}

void Network::sendScore()
{

}

void Network::receiveBoard(Board *leftBoard, Board *rightBoard)
{
	socket.receive(packet);
	if (packet.getDataSize() == 0)
	{
		return;
	}

	int packetData;
	Board *adjacentBoard;

	packet >> packetData;
	if (packetData == -1)
	{
		adjacentBoard = leftBoard;
	}
	else
	{
		adjacentBoard = rightBoard;
	}

	socket.receive(packet);

	for (int j = 0; j < adjacentBoard->getSize().y; ++j)
	{
		for (int i = 0; i < adjacentBoard->getSize().x; ++i)
		{
			packet >> packetData;
			if (packetData == 0)
			{
				adjacentBoard->grid[i][j].setTexture(adjacentBoard->emptyTex);
			}
			else
			{
				adjacentBoard->grid[i][j].setTexture(adjacentBoard->blockTex);
				if (packetData == 1)
				{
					adjacentBoard->grid[i][j].setColor(sf::Color::Cyan);
				}
				else if (packetData == 2)
				{
					adjacentBoard->grid[i][j].setColor(sf::Color::Yellow);
				}
				else if (packetData == 3)
				{
					adjacentBoard->grid[i][j].setColor(sf::Color::Red);
				}
				else if (packetData == 4)
				{
					adjacentBoard->grid[i][j].setColor(sf::Color::Green);
				}
				else if (packetData == 5)
				{
					adjacentBoard->grid[i][j].setColor(sf::Color(255, 130, 0));
				}
				else if (packetData == 6)
				{
					adjacentBoard->grid[i][j].setColor(sf::Color::Blue);
				}
				else if (packetData == 7)
				{
					adjacentBoard->grid[i][j].setColor(sf::Color::Magenta);
				}
			}
		}
	}
}

void Network::receiveScore()
{

}