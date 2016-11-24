#include "Board.h"


Board::Board(sf::Vector2u boardSize, sf::Vector2i boardPos, sf::Vector2u spawn)
{
	blockTex.loadFromFile("../Assets/Block.png");
	emptyTex.loadFromFile("../Assets/Brick2.png");
	block.setTexture(emptyTex);

	size = boardSize;
	position = boardPos;
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
			grid[i][j] = block;
			grid[i][j].setPosition(position.x + block.getGlobalBounds().width * i, position.y + block.getGlobalBounds().height * j);
		}
	}

	gridSlice.resize(boardSize.y);
	for (int i = 0; i < size.y; ++i)
	{
		block = grid[size.x - 1][i];
		block.move(blockSize.x, 0);
		gridSlice[i] = block;
	}
}


Board::~Board()
{
}

sf::Vector2u Board::getSize()
{
	return size;
}

sf::Vector2i Board::getPosition()
{
	return position;
}

sf::Vector2u Board::getSpawnPoint()
{
	return spawnPoint;
}