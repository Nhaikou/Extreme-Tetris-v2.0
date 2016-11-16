#include "Factory.h"

Factory::Factory(StateMachine* sm, sf::Vector2u size, Server *srvr)
{
	stateMachine = sm;
	boardSize = size;
	server = srvr;
}

Factory::~Factory()
{
	delete board;
	delete currentBlock;
}

void Factory::onInitialize()
{
	board = new Board(boardSize, sf::Vector2i(0, -2), sf::Vector2u(3, 3));
	lineTime.y = 500;
	board->dropTime.y = 1000;
	board->counter = 0;
	board->maxRows;
	board->dropTimeReduction;
}

void Factory::handleInput()
{

}

void Factory::update(const float dt)
{
	bool updateClient = false;

	for (int i = 0; i < server->clients.size(); ++i)
	{
		clientKey = server->receiveButtonPress(0);
	}
	
	if (clientKey == sf::Keyboard::Escape || sf::Keyboard::Left || sf::Keyboard::Right || sf::Keyboard::Down || sf::Keyboard::Z || sf::Keyboard::X)
	{
		updateClient = true;
	}

	if (clientKey == sf::Keyboard::Escape)
	{
		updateClient = true;
		stateMachine->popState();
		return;
	}
	if (clientKey == sf::Keyboard::Left)
	{
		currentBlock->moveLeft();
	}
	if (clientKey == sf::Keyboard::Right)
	{
		currentBlock->moveRight();
	}
	if (clientKey == sf::Keyboard::Down)
	{
		if (!currentBlock->moveDown())
		{
			
		}
	}
	if (clientKey == sf::Keyboard::Z)
	{
		currentBlock->rotate(-1);
	}
	if (clientKey == sf::Keyboard::X)
	{
		currentBlock->rotate(1);
	}

	board->dropTime.x += dt;
	if (board->dropTime.x >= board->dropTime.y)
	{
		board->dropTime.x = 0;
		if (!currentBlock->moveDown())
		{
			
		}
		updateClient = true;
	}

	lineTime.x += dt;
	if (lineTime.x >= lineTime.y)
	{
		lineTime.x = 0;
		if (lineDirection == -1)
		{
			moveLineLeft();
			//server->sendRenderTexture(sf::Vector2f(0, 0), stateMachine->window.getSize());
		}
		else
		{
			moveLineRight();
			//server->sendRenderTexture(sf::Vector2f(0, 0), stateMachine->window.getSize());
		}
	}

	if (updateClient)
	{
		clientKey = -1;
	}
}

void Factory::draw(const float dt)
{

}

void Factory::moveLineLeft()
{
	bool hitCurrentBlock = false;

	for (int j = 0; j < board->getSize().y; ++j)
	{
		for (int i = 0; i < board->getSize().x; ++i)
		{
			board->updatedGrid[i][j].z = BlockType::EMPTY;
		}
	}

	for (int j = 0; j < board->getSize().y; ++j)
	{
		for (int i = 0; i < board->getSize().x; ++i)
		{
			if (!(currentBlock->positions[0] == sf::Vector2i(i, j) || currentBlock->positions[1] == sf::Vector2i(i, j) ||
				currentBlock->positions[2] == sf::Vector2i(i, j) || currentBlock->positions[3] == sf::Vector2i(i, j)))
			{
				if (board->grid[i][j].z == BlockType::EMPTY)
				{
					if (i == 0)
					{
						if (currentBlock->positions[0] == sf::Vector2i(board->getSize().x - 1, j) || currentBlock->positions[1] == sf::Vector2i(board->getSize().x - 1, j) ||
							currentBlock->positions[2] == sf::Vector2i(board->getSize().x - 1, j) || currentBlock->positions[3] == sf::Vector2i(board->getSize().x - 1, j))
						{
							hitCurrentBlock = true;
						}
						board->updatedGrid[board->getSize().x - 1][j].z = board->grid[i][j].z;
					}
					else
					{
						if (currentBlock->positions[0] == sf::Vector2i(i - 1, j) || currentBlock->positions[1] == sf::Vector2i(i - 1, j) ||
							currentBlock->positions[2] == sf::Vector2i(i - 1, j) || currentBlock->positions[3] == sf::Vector2i(i - 1, j))
						{
							hitCurrentBlock = true;
						}
						board->updatedGrid[i - 1][j].z = board->grid[i][j].z;
					}
				}
			}
		}
	}

	if (hitCurrentBlock)
	{
		bool blockWrapped = false;
		for (int i = 0; i < currentBlock->tetra; ++i)
		{
			currentBlock->positions[i].x--;
			if (currentBlock->positions[i].x == -1)
			{
				currentBlock->positions[i].x = board->getSize().x - 1;
				blockWrapped = true;
			}
			board->updatedGrid[currentBlock->positions[i].x][currentBlock->positions[i].y].z = currentBlock->getType();
		}
		board->grid = board->updatedGrid;
		if (blockWrapped)
		{
			while (true)
			{
				if (!currentBlock->moveDown())
				{
					
					return;
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < currentBlock->tetra; ++i)
		{
			board->updatedGrid[currentBlock->positions[i].x][currentBlock->positions[i].y].z = currentBlock->getType();
		}
		board->grid = board->updatedGrid;
	}
}

void Factory::moveLineRight()
{
	bool hitCurrentBlock = false;

	for (int j = 0; j < board->getSize().y; ++j)
	{
		for (int i = 0; i < board->getSize().x; ++i)
		{
			board->updatedGrid[i][j].z = BlockType::EMPTY;
		}
	}

	for (int j = 0; j < board->getSize().y; ++j)
	{
		for (int i = 0; i < board->getSize().x; ++i)
		{
			if (!(currentBlock->positions[0] == sf::Vector2i(i, j) || currentBlock->positions[1] == sf::Vector2i(i, j) ||
				currentBlock->positions[2] == sf::Vector2i(i, j) || currentBlock->positions[3] == sf::Vector2i(i, j)))
			{
				if (board->grid[i][j].z == BlockType::EMPTY)
				{
					if (i == board->getSize().x - 1)
					{
						if (currentBlock->positions[0] == sf::Vector2i(0, j) || currentBlock->positions[1] == sf::Vector2i(0, j) ||
							currentBlock->positions[2] == sf::Vector2i(0, j) || currentBlock->positions[3] == sf::Vector2i(0, j))
						{
							hitCurrentBlock = true;
						}
						board->updatedGrid[0][j].z = board->grid[i][j].z;
					}
					else
					{
						if (currentBlock->positions[0] == sf::Vector2i(i + 1, j) || currentBlock->positions[1] == sf::Vector2i(i + 1, j) ||
							currentBlock->positions[2] == sf::Vector2i(i + 1, j) || currentBlock->positions[3] == sf::Vector2i(i + 1, j))
						{
							hitCurrentBlock = true;
						}
						board->updatedGrid[i + 1][j].z = board->grid[i][j].z;
					}
				}
			}
		}
	}

	if (hitCurrentBlock)
	{
		bool blockWrapped = false;
		for (int i = currentBlock->tetra - 1; i >= 0; --i)
		{
			currentBlock->positions[i].x++;
			if (currentBlock->positions[i].x == board->getSize().x)
			{
				currentBlock->positions[i].x = 0;
				blockWrapped = true;
			}
			board->updatedGrid[currentBlock->positions[i].x][currentBlock->positions[i].y].z = currentBlock->getType();
		}
		board->grid = board->updatedGrid;
		if (blockWrapped)
		{
			while (true)
			{
				if (!currentBlock->moveDown())
				{
					
					return;
				}
			}
		}
	}
	else
	{
		for (int i = currentBlock->tetra - 1; i >= 0; --i)
		{
			board->updatedGrid[currentBlock->positions[i].x][currentBlock->positions[i].y].z = currentBlock->getType();
		}
		board->grid = board->updatedGrid;
	}
}
