#include "Board.h"


Board::Board(sf::Vector2u boardSize, sf::Vector2i boardPos, sf::Vector2u spawn, bool lastPlayer)
{
	blockTex.loadFromFile("../Assets/Block.png");
	emptyTex.loadFromFile("../Assets/Brick2.png");
	wallTex.loadFromFile("../Assets/Brick.png");
	floorTex.loadFromFile("../Assets/Brick3.png");
	block.setTexture(emptyTex);
	wall.setTexture(wallTex);
	floor.setTexture(floorTex);

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

			if (i == 0)
			{
				wall.setPosition(grid[i][j].getPosition() - sf::Vector2f(blockSize.x, 0));
				walls.push_back(wall);
			}
			if (i == size.x - 1 && lastPlayer)
			{
				wall.setPosition(grid[i][j].getPosition() + sf::Vector2f(blockSize.x, 0));
				walls.push_back(wall);
			}
			if (j == size.y - 1)
			{
				floor.setPosition(grid[i][j].getPosition() + sf::Vector2f(0, blockSize.y));
				walls.push_back(floor);
			}
		}
	}

	floor.setPosition(grid[0][size.y - 1].getPosition().x - blockSize.x, grid[0][size.y - 1].getPosition().y + blockSize.y);
	walls.push_back(floor);
	if (lastPlayer)
	{
		floor.setPosition(grid[size.x - 1][size.y - 1].getPosition() + sf::Vector2f(blockSize.x, blockSize.y));
		walls.push_back(floor);
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