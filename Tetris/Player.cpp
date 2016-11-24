#include "Player.h"


Player::Player(unsigned id, sf::Vector2i position, sf::Vector2u size, sf::Vector2u spawn)
{
	board = new Board(size, spawn);
	board->dropTime.y = 1000;
	board->counter = 0;
	board->maxRows;
	board->dropTimeReduction;
}

Player::~Player()
{
	delete board;
	delete currentBlock;
}

bool Player::updateClient()
{
	bool updated = false;
	if (clientKey == sf::Keyboard::Left || sf::Keyboard::Right || clientKey == sf::Keyboard::Down || sf::Keyboard::Z || sf::Keyboard::X)
	{
		updated = true;
	}

	board->updatedGrid = board->grid;

	if (clientKey == sf::Keyboard::Left)
	{
		score.x = 0;
		currentBlock->moveLeft();
	}
	if (clientKey == sf::Keyboard::Right)
	{
		score.x = 0;
		currentBlock->moveRight();
	}
	if (clientKey == sf::Keyboard::Up)
	{
		score.x = currentBlock->hardDrop();
		spawnBlock();
	}
	if (clientKey == sf::Keyboard::Down)
	{
		score.x++;
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
	return updated;
}

bool Player::spawnBlock()
{
	score.y += score.x;
	score.x = 0;

	score.y += board->clearRow();

	blockSpawned = true;
	unsigned randomBlock = nextBlock;
	if (currentBlock != nullptr)
	{
		delete currentBlock;
	}
	if (randomBlock == BlockType::BLOCKI)
	{
		currentBlock = new BlockI(board);
	}
	if (randomBlock == BlockType::BLOCKO)
	{
		currentBlock = new BlockO(board);
	}
	if (randomBlock == BlockType::BLOCKZ)
	{
		currentBlock = new BlockZ(board);
	}
	if (randomBlock == BlockType::BLOCKS)
	{
		currentBlock = new BlockS(board);
	}
	if (randomBlock == BlockType::BLOCKL)
	{
		currentBlock = new BlockL(board);
	}
	if (randomBlock == BlockType::BLOCKJ)
	{
		currentBlock = new BlockJ(board);
	}
	if (randomBlock == BlockType::BLOCKT)
	{
		currentBlock = new BlockT(board);
	}

	if (!currentBlock->spawn())
	{
		return false;
	}
	return true;
}

bool Player::dropUpdate(const float dt)
{
	board->dropTime.x += dt;
	if (board->dropTime.x >= board->dropTime.y)
	{
		board->updatedGrid = board->grid;
		board->dropTime.x = 0;
		score.x = 0;
		if (!currentBlock->moveDown())
		{
			spawnBlock();
		}
		return true;
	}
	return false;
}