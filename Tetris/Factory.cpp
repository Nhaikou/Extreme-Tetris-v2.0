#include "Factory.h"

Factory::Factory(StateMachine* sm, sf::Vector2u size, Network *net)
{
	stateMachine = sm;
	boardSize = size;
	network = net;
}

Factory::~Factory()
{
	delete board;
	delete currentBlock;
}

void Factory::onInitialize()
{
	if (network == nullptr)
	{
		board = new Board(boardSize, sf::Vector2i(0, -2), sf::Vector2u(3, 3));
	}
	else
	{
		leftBoard = new Board(boardSize, sf::Vector2i(0, -1), sf::Vector2u(3, 3));
		board = new Board(boardSize, sf::Vector2i(boardSize.x, -1), sf::Vector2u(3, 3));
		rightBoard = new Board(boardSize, sf::Vector2i(boardSize.x * 2, -1), sf::Vector2u(3, 3));
	}
	dropTime.y = 1000;
	lineTime.y = 800;
	spawnBlock();
}

void Factory::handleInput()
{
	if (stateMachine->event.type == sf::Event::KeyPressed)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			stateMachine->popState();
			return;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			currentBlock->moveLeft();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			currentBlock->moveRight();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			if (!currentBlock->moveDown())
			{
				spawnBlock();
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			currentBlock->rotate(-1);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		{
			currentBlock->rotate(1);
		}
		if (network != nullptr)
		{
			network->sendBoard(board);
		}
	}
}

void Factory::update(const float dt)
{
	dropTime.x += dt;
	if (dropTime.x >= dropTime.y)
	{
		dropTime.x = 0;
		if (!currentBlock->moveDown())
		{
			spawnBlock();
		}
		if (network != nullptr)
		{
			network->sendBoard(board);
		}
	}

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
		if (network != nullptr)
		{
			network->sendBoard(board);
		}
	}

	if (network != nullptr)
	{
		network->receiveBoard(leftBoard, rightBoard);
		network->receiveScore();
	}
}

void Factory::draw(const float dt)
{
	for (int j = 0; j < board->getSize().y; ++j)
	{
		for (int i = 0; i < board->getSize().x; ++i)
		{
			stateMachine->window.draw(board->grid[i][j]);
			if (network != nullptr)
			{
				stateMachine->window.draw(leftBoard->grid[i][j]);
				stateMachine->window.draw(rightBoard->grid[i][j]);
			}
		}
	}
}

void Factory::spawnBlock()
{
	if (network != nullptr)
	{
		network->sendScore();
	}

	unsigned randomBlock = rand() % 7;
	if (currentBlock != nullptr)
	{
		delete currentBlock;
	}
	if (randomBlock == 0)
	{
		currentBlock = new BlockI(board);
	}
	if (randomBlock == 1)
	{
		currentBlock = new BlockO(board);
	}
	if (randomBlock == 2)
	{
		currentBlock = new BlockZ(board);
	}
	if (randomBlock == 3)
	{
		currentBlock = new BlockS(board);
	}
	if (randomBlock == 4)
	{
		currentBlock = new BlockL(board);
	}
	if (randomBlock == 5)
	{
		currentBlock = new BlockJ(board);
	}
	if (randomBlock == 6)
	{
		currentBlock = new BlockT(board);
	}
	if (!currentBlock->spawn())
	{
		stateMachine->window.close();
	}
}

void Factory::moveLineLeft()
{
	bool hitCurrentBlock = false;

	for (int j = 0; j < board->getSize().y; ++j)
	{
		for (int i = 0; i < board->getSize().x; ++i)
		{
			board->updatedGrid[i][j].setTexture(board->emptyTex);
		}
	}

	for (int j = 0; j < board->getSize().y; ++j)
	{
		for (int i = 0; i < board->getSize().x; ++i)
		{
			if (!(currentBlock->positions[0] == sf::Vector2i(i, j) || currentBlock->positions[1] == sf::Vector2i(i, j) ||
				currentBlock->positions[2] == sf::Vector2i(i, j) || currentBlock->positions[3] == sf::Vector2i(i, j)))
			{
				if (board->grid[i][j].getTexture() == &board->blockTex)
				{
					if (i == 0)
					{
						if (currentBlock->positions[0] == sf::Vector2i(board->getSize().x - 1, j) || currentBlock->positions[1] == sf::Vector2i(board->getSize().x - 1, j) ||
							currentBlock->positions[2] == sf::Vector2i(board->getSize().x - 1, j) || currentBlock->positions[3] == sf::Vector2i(board->getSize().x - 1, j))
						{
							hitCurrentBlock = true;
						}
						board->updatedGrid[board->getSize().x - 1][j].setTexture(board->blockTex);
						board->updatedGrid[board->getSize().x - 1][j].setColor(board->grid[i][j].getColor());
					}
					else
					{
						if (currentBlock->positions[0] == sf::Vector2i(i - 1, j) || currentBlock->positions[1] == sf::Vector2i(i - 1, j) ||
							currentBlock->positions[2] == sf::Vector2i(i - 1, j) || currentBlock->positions[3] == sf::Vector2i(i - 1, j))
						{
							hitCurrentBlock = true;
						}
						board->updatedGrid[i - 1][j].setTexture(board->blockTex);
						board->updatedGrid[i - 1][j].setColor(board->grid[i][j].getColor());
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
			board->updatedGrid[currentBlock->positions[i].x][currentBlock->positions[i].y].setTexture(board->blockTex);
			board->updatedGrid[currentBlock->positions[i].x][currentBlock->positions[i].y].setColor(currentBlock->getColor());
		}
		board->grid = board->updatedGrid;
		if (blockWrapped)
		{
			while (true)
			{
				if (!currentBlock->moveDown())
				{
					spawnBlock();
					return;
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < currentBlock->tetra; ++i)
		{
			board->updatedGrid[currentBlock->positions[i].x][currentBlock->positions[i].y].setTexture(board->blockTex);
			board->updatedGrid[currentBlock->positions[i].x][currentBlock->positions[i].y].setColor(currentBlock->getColor());
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
			board->updatedGrid[i][j].setTexture(board->emptyTex);
		}
	}

	for (int j = 0; j < board->getSize().y; ++j)
	{
		for (int i = 0; i < board->getSize().x; ++i)
		{
			if (!(currentBlock->positions[0] == sf::Vector2i(i, j) || currentBlock->positions[1] == sf::Vector2i(i, j) ||
				currentBlock->positions[2] == sf::Vector2i(i, j) || currentBlock->positions[3] == sf::Vector2i(i, j)))
			{
				if (board->grid[i][j].getTexture() == &board->blockTex)
				{
					if (i == board->getSize().x - 1)
					{
						if (currentBlock->positions[0] == sf::Vector2i(0, j) || currentBlock->positions[1] == sf::Vector2i(0, j) ||
							currentBlock->positions[2] == sf::Vector2i(0, j) || currentBlock->positions[3] == sf::Vector2i(0, j))
						{
							hitCurrentBlock = true;
						}
						board->updatedGrid[0][j].setTexture(board->blockTex);
						board->updatedGrid[0][j].setColor(board->grid[i][j].getColor());
					}
					else
					{
						if (currentBlock->positions[0] == sf::Vector2i(i + 1, j) || currentBlock->positions[1] == sf::Vector2i(i + 1, j) ||
							currentBlock->positions[2] == sf::Vector2i(i + 1, j) || currentBlock->positions[3] == sf::Vector2i(i + 1, j))
						{
							hitCurrentBlock = true;
						}
						board->updatedGrid[i + 1][j].setTexture(board->blockTex);
						board->updatedGrid[i + 1][j].setColor(board->grid[i][j].getColor());
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
			board->updatedGrid[currentBlock->positions[i].x][currentBlock->positions[i].y].setTexture(board->blockTex);
			board->updatedGrid[currentBlock->positions[i].x][currentBlock->positions[i].y].setColor(currentBlock->getColor());
		}
		board->grid = board->updatedGrid;
		if (blockWrapped)
		{
			while (true)
			{
				if (!currentBlock->moveDown())
				{
					spawnBlock();
					return;
				}
			}
		}
	}
	else
	{
		for (int i = currentBlock->tetra - 1; i >= 0; --i)
		{
			board->updatedGrid[currentBlock->positions[i].x][currentBlock->positions[i].y].setTexture(board->blockTex);
			board->updatedGrid[currentBlock->positions[i].x][currentBlock->positions[i].y].setColor(currentBlock->getColor());
		}
		board->grid = board->updatedGrid;
	}
}
