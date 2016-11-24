#include "Board.h"

Board::Board(sf::Vector2u boardSize, sf::Vector2u spawn)
{
	size = boardSize;
	spawnPoint = spawn;

	// Resizing the grid to fit all the blocks
	grid.resize(size.x);
	for (int i = 0; i < size.x; ++i)
	{
		grid[i].resize(size.y);
	}

	// Putting the blocks to their places with an empty texture
	for (int j = 0; j < size.y; ++j)
	{
		for (int i = 0; i < size.x; ++i)
		{
			grid[i][j] = BlockType::EMPTY;
		}
	}

	// UpdatedGrid is the same as grid until it's needed somewhere else
	updatedGrid = grid;

	// Our grid is now ready and all we need to do now is to change textures and colors to make it look like the blocks are moving

	// Factory things
	gridSlice.resize(size.y);
	for (int i = 0; i < size.y; ++i)
	{
		gridSlice[i] = BlockType::EMPTY;
	}

	// Initializing points gained by clearing rows
	pointsPerRow.push_back(40);		// One row cleared
	pointsPerRow.push_back(100);	// Two rows cleared
	pointsPerRow.push_back(300);	// Three rows cleared
	pointsPerRow.push_back(1200);	// Four rows cleared
}

Board::~Board()
{

}

sf::Vector2u Board::getSize()
{
	return size;
}

sf::Vector2u Board::getSpawnPoint()
{
	return spawnPoint;
}

unsigned Board::clearRow()
{
	unsigned blocksOnRow = 0, tempClearedRows = 0, score = 0;

	for (int j = 0; j < size.y; ++j)
	{
		for (int i = 0; i < size.x; ++i)
		{
			if (grid[i][j] != BlockType::EMPTY)
			{
				++blocksOnRow;
				if (blocksOnRow == size.x)
				{
					for (int k = 0; k < size.x; ++k)
					{
						grid[k][j] = BlockType::EMPTY;
					}
					dropRow(j);
					tempClearedRows++;
				}
			}
		}
		blocksOnRow = 0;
	}

	if (tempClearedRows > 0)
	{
		score += pointsPerRow[tempClearedRows - 1] * (level + 1);
		dropTime.x = 0;
	}

	clearedRows += tempClearedRows;
	if (clearedRows >= maxRows)
	{
		dropTime.y -= dropTimeReduction;
		clearedRows -= maxRows;
		level++;
	}

	return score;
}

void Board::dropRow(int y)
{
	for (int j = y; j > 0; --j)
	{
		for (int i = 0; i < size.x; ++i)
		{
			grid[i][j] = grid[i][j - 1];
		}
	}
}