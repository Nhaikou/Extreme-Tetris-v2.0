#include "Network.h"


Network::Network()
{
}


Network::~Network()
{
}

void Network::sendBoard(Board *board)
{
	packet << playerNumber;

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
			}
		}
	}
}

void Network::sendScore()
{

}

void Network::receiveBoard(Board *leftBoard, Board *rightBoard)
{
	unsigned packetData;
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
			}
		}
	}
}

void Network::receiveScore()
{

}