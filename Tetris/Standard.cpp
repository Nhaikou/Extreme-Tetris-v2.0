#include "Standard.h"

Standard::Standard(StateMachine* sm)
{
	stateMachine = sm;
}

Standard::~Standard()
{
	delete board;
	delete currentBlock;
}

void Standard::onInitialize()
{
	board = new Board(sf::Vector2u(10, 19), sf::Vector2i(0, -16), sf::Vector2u(3, 2));
	dropTime.y = 1000;
	spawnBlock();
}

void Standard::handleInput()
{
	if (stateMachine->event.type == sf::Event::KeyPressed)
	{
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

void Standard::update(const float dt)
{
	dropTime.x += dt;
	if (dropTime.x >= dropTime.y)
	{
		dropTime.x = 0;
		if (!currentBlock->moveDown())
		{
			spawnBlock();
		}
	}
}

void Standard::draw(const float dt)
{
	for (int j = 0; j < board->getBoardSize().y; j++)
	{
		for (int i = 0; i < board->getBoardSize().x; i++)
		{
			stateMachine->window.draw(board->board[i][j]);
		}
	}
}

void Standard::spawnBlock()
{
	unsigned randomBlock = rand() % 1;
	if (currentBlock != nullptr)
	{
		delete currentBlock;
	}
	if (randomBlock == 0)
	{
		currentBlock = new BlockI(board);
	}
	if (!currentBlock->spawn())
	{
		stateMachine->window.close();
	}
}