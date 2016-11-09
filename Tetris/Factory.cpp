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
	spawnBlock();
	server->renderTexture.create(stateMachine->window.getSize().x, stateMachine->window.getSize().y);
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
	}
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
			spawnBlock();
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
			spawnBlock();
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
		MinMaxPositions minMax = currentBlock->calculateMinAndMaxPositions();
		server->sendRenderTexture(sf::Vector2f(minMax.minX, minMax.minY), sf::Vector2u(minMax.maxX, minMax.maxY));
		clientKey = -1;
	}
}

void Factory::draw(const float dt)
{
	server->renderTexture.clear(sf::Color::Black);
	for (int j = 0; j < board->getSize().y; ++j)
	{
		for (int i = 0; i < board->getSize().x; ++i)
		{
			if (server->networking)
			{
				server->renderTexture.draw(board->grid[i][j]);
			}
			else
			{
				stateMachine->window.draw(board->grid[i][j]);
			}
		}
	}
	server->renderTexture.display();
}

void Factory::spawnBlock()
{
	board->counter += board->clearRow();
	if (board->counter >= board->maxRows)
	{
		board->dropTime.y -= board->dropTimeReduction;
		board->counter -= board->maxRows;
		std::cout << "Current drop speed: " << board->dropTime.y << std::endl;
	}


	unsigned randomBlock = bag.getNextBlock();
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
