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
	board = new Board(sf::Vector2u(10, 20), sf::Vector2i(0, -1), sf::Vector2u(3, 3));
	board->dropTime.y = 1000;
	board->counter = 0;
	board->maxRows;
	board->dropTimeReduction;
	spawnBlock();

	if (!font.loadFromFile("../Assets/8bitOperatorPlus8-Bold.ttf"))
	{
		std::cout << "Error loading font" << std::endl;
	}
	scoreText.setFont(font);
	scoreText.setColor(sf::Color::White);
	scoreText.setCharacterSize(12);
	scoreText.setPosition(300, 10);
}

void Standard::handleInput()
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

void Standard::update(const float dt)
{
	ss.str("");
	ss << board->getScore();
	scoreText.setString(ss.str());
	board->dropTime.x += dt;
	if (board->dropTime.x >= board->dropTime.y)
	{
		board->dropTime.x = 0;
		if (!currentBlock->moveDown())
		{
			spawnBlock();
		}
	}
}

void Standard::draw(const float dt)
{
	for (int j = 0; j < board->getSize().y; ++j)
	{
		for (int i = 0; i < board->getSize().x; ++i)
		{
			stateMachine->window.draw(board->grid[i][j]);
		}
	}
	stateMachine->window.draw(scoreText);
}

void Standard::spawnBlock()
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