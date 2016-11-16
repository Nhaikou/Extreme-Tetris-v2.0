#include "BlockZ.h"


BlockZ::BlockZ(Board* b) : Block(b)
{
	board = b;
}


BlockZ::~BlockZ()
{

}

bool BlockZ::spawn()
{
	type = BlockType::BLOCKZ;

	if (board->grid[board->getSpawnPoint().x][board->getSpawnPoint().y].z == BlockType::EMPTY &&
		board->grid[board->getSpawnPoint().x + 1][board->getSpawnPoint().y].z == BlockType::EMPTY &&
		board->grid[board->getSpawnPoint().x + 1][board->getSpawnPoint().y + 1].z == BlockType::EMPTY &&
		board->grid[board->getSpawnPoint().x + 2][board->getSpawnPoint().y + 1].z == BlockType::EMPTY)
	{
		positions[1] = sf::Vector2i(board->getSpawnPoint().x, board->getSpawnPoint().y);
		board->grid[positions[1].x][positions[1].y].z = BlockType::BLOCKZ;

		positions[2] = sf::Vector2i(board->getSpawnPoint().x + 1, board->getSpawnPoint().y);
		board->grid[positions[2].x][positions[2].y].z = BlockType::BLOCKZ;

		positions[0] = sf::Vector2i(board->getSpawnPoint().x + 1, board->getSpawnPoint().y + 1);
		board->grid[positions[0].x][positions[0].y].z = BlockType::BLOCKZ;

		positions[3] = sf::Vector2i(board->getSpawnPoint().x + 2, board->getSpawnPoint().y + 1);
		board->grid[positions[3].x][positions[3].y].z = BlockType::BLOCKZ;
	}
	
	else
	{
		return false;
	}

	return true;
}

void BlockZ::rotate(int direction)
{
	for (int i = 0; i < tetra; ++i)
	{
		board->grid[positions[i].x][positions[i].y].z = BlockType::EMPTY;
	}

	// Rotate
	if (rotation == 0 && positions[1].y > 0 &&
		board->grid[positions[0].x - 1][positions[0].y].z == BlockType::EMPTY &&
		board->grid[positions[3].x - 1][positions[3].y - 2].z == BlockType::EMPTY)
	{
		positions[0] += sf::Vector2i(-1, 0);
		positions[3] += sf::Vector2i(-1, -2);

		rotation = 1;
	}
	else if (rotation == 1 && positions[3].x + 1 < board->getSize().x &&
		board->grid[positions[0].x + 1][positions[0].y].z == BlockType::EMPTY &&
		board->grid[positions[3].x + 1][positions[3].y + 2].z == BlockType::EMPTY)
	{
		positions[0] += sf::Vector2i(1, 0);
		positions[3] += sf::Vector2i(1, 2);

		rotation = 0;
	}

	for (int i = 0; i < tetra; ++i)
	{
		board->grid[positions[i].x][positions[i].y].z = BlockType::BLOCKZ;
	}
}
