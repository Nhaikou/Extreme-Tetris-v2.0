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

	unsigned counter = 0;
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 1; j >= 0; --j)
		{
			if (board->grid[board->getSpawnPoint().x + i][board->getSpawnPoint().y + j].z == BlockType::EMPTY)
			{ 
				positions[counter] = sf::Vector2i(board->getSpawnPoint().x + i, board->getSpawnPoint().y + j);
				board->grid[positions[i].x][positions[i].y].z = BlockType::BLOCKO;
				counter++;
			}
			else
			{
				return false;
			}
		}
	}
	return true;
}