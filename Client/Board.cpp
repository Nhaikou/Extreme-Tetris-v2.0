#include "Board.h"


Board::Board(sf::Vector2u boardSize, sf::Vector2i boardPos, sf::Vector2u spawn)
{
	blockTex.loadFromFile("../Assets/Block.png");
	block.setTexture(blockTex);
	emptyTex.create(blockTex.getSize().x, blockTex.getSize().y); // Create an empty texture that is the same size as Block.png
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