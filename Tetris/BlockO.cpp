#include "BlockO.h"


BlockO::BlockO(Board* b) : Block(b)
{
	board = b;
}


BlockO::~BlockO()
{

}

bool BlockO::spawn()
{
	type = BlockType::BLOCKO;

	if (board->grid[board->getSpawnPoint().x + 1][board->getSpawnPoint().y] == BlockType::EMPTY &&
		board->grid[board->getSpawnPoint().x + 2][board->getSpawnPoint().y] == BlockType::EMPTY &&
		board->grid[board->getSpawnPoint().x + 1][board->getSpawnPoint().y + 1] == BlockType::EMPTY &&
		board->grid[board->getSpawnPoint().x + 2][board->getSpawnPoint().y + 1] == BlockType::EMPTY)
	{
		positions[0] = sf::Vector2i(board->getSpawnPoint().x + 1, board->getSpawnPoint().y + 1);
		board->grid[positions[0].x][positions[0].y] = BlockType::BLOCKO;

		positions[1] = sf::Vector2i(board->getSpawnPoint().x + 1, board->getSpawnPoint().y);
		board->grid[positions[1].x][positions[1].y] = BlockType::BLOCKO;

		positions[2] = sf::Vector2i(board->getSpawnPoint().x + 2, board->getSpawnPoint().y + 1);
		board->grid[positions[2].x][positions[2].y] = BlockType::BLOCKO;

		positions[3] = sf::Vector2i(board->getSpawnPoint().x + 2, board->getSpawnPoint().y);
		board->grid[positions[3].x][positions[3].y] = BlockType::BLOCKO;
	}
	else
	{
		return false;
	}

	return true;
}