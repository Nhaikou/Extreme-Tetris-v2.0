#include "BlockI.h"

BlockI::BlockI(Board *b) : Block(b)
{
	
}

BlockI::~BlockI()
{

}

bool BlockI::spawn()
{
	type = BlockType::BLOCKI;
	for (int i = 0; i < tetra; ++i)
	{
		if (board->grid[board->getSpawnPoint().x + i][board->getSpawnPoint().y].z == BlockType::EMPTY)
		{
			positions[i] = sf::Vector2i(board->getSpawnPoint().x + i, board->getSpawnPoint().y);
			board->grid[positions[i].x][positions[i].y].z = BlockType::BLOCKI;
		}
		else
		{
			return false;
		}
	}
	return true;
}

void BlockI::rotate(int direction)
{
	for (int i = 0; i < tetra; ++i)
	{
		board->grid[positions[i].x][positions[i].y].z = BlockType::EMPTY;
	}

	if (rotation == 1 && positions[1].x > 0 && positions[1].x + 2 < board->getSize().x &&
		board->grid[positions[0].x - 1][positions[0].y - 1].z == BlockType::EMPTY &&
		board->grid[positions[2].x + 1][positions[2].y + 1].z == BlockType::EMPTY &&
		board->grid[positions[3].x + 2][positions[3].y + 2].z == BlockType::EMPTY)
	{
		positions[0] += sf::Vector2i(-1, -1);
		positions[2] += sf::Vector2i(1, 1);
		positions[3] += sf::Vector2i(2, 2);

		rotation = 0;
	}
	else if (rotation == 0 && positions[1].y - 1 > 0 && positions[1].y + 1 < board->getSize().y &&
		board->grid[positions[0].x + 1][positions[0].y + 1].z == BlockType::EMPTY &&
		board->grid[positions[2].x - 1][positions[2].y - 1].z == BlockType::EMPTY &&
		board->grid[positions[3].x - 2][positions[3].y - 2].z == BlockType::EMPTY)
	{
		positions[0] += sf::Vector2i(1, 1);
		positions[2] += sf::Vector2i(-1, -1);
		positions[3] += sf::Vector2i(-2, -2);

		rotation = 1;
	}

	for (int i = 0; i < tetra; ++i)
	{
		board->grid[positions[i].x][positions[i].y].z = BlockType::BLOCKI;
	}
}