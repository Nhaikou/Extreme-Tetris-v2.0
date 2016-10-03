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
	board = new Board(sf::Vector2u(10, 16), sf::Vector2u(0, 0));
	currentBlock = new BlockI;
}

void Standard::handleInput()
{
	if (stateMachine->event.type == sf::Event::KeyPressed)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			currentBlock->moveLeft(board);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			currentBlock->moveRight(board);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			currentBlock->moveDown(board);
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
	std::cout << currentBlock->rotation << std::endl;
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