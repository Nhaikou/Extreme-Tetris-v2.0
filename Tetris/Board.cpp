#include "Board.h"

Board::Board(sf::Vector2u size, sf::Vector2i boardPos, sf::Vector2u spawn)
{
	// Resource loading
	blockTex.loadFromFile("../Assets/Block.png");
	block.setTexture(blockTex);
	emptyTex.create(blockTex.getSize().x, blockTex.getSize().y); // Create an empty texture that is the same size as Block.png
	block.setTexture(emptyTex);

	boardSize = size;
	boardPosition = sf::Vector2i(boardPos.x * block.getGlobalBounds().width, boardPos.y * block.getGlobalBounds().height); // The position varies according to the texture's size
	spawnPoint = spawn;

	// Resizing the grid to fit all the blocks
	grid.resize(boardSize.x);
	for (int i = 0; i < boardSize.x; ++i)
	{
		grid[i].resize(boardSize.y);
	}

	// Putting the blocks to their places with an empty texture
	for (int j = 0; j < boardSize.y; ++j)
	{
		for (int i = 0; i < boardSize.x; ++i)
		{
			grid[i][j] = block;
			grid[i][j].setPosition(boardPosition.x + block.getGlobalBounds().width * i, boardPosition.y + block.getGlobalBounds().height * j);
		}
	}

	// UpdatedGrid is the same as grid until it's needed somewhere else
	updatedGrid = grid;

	// Our grid is now ready and all we need to do now is to change textures and colors to make it look like the blocks are moving

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
	return boardSize;
}

sf::Vector2i Board::getBoardPosition()
{
	return boardPosition;
}

sf::Vector2u Board::getSpawnPoint()
{
	return spawnPoint;
}

unsigned Board::getScore()
{
	return score;
}

unsigned Board::getLevel()
{
	return level;
}

void Board::setScore(unsigned scr)
{
	score = scr;
}

void Board::setLevel(unsigned lvl)
{
	level = lvl;
}

unsigned Board::clearRow()
{
	unsigned counter = 0;
	unsigned clearedRows = 0;

	for (int j = 0; j < boardSize.y; ++j)
	{
		for (int i = 0; i < boardSize.x; ++i)
		{
			if (grid[i][j].getTexture() == &blockTex)
			{
				++counter;
				if (counter == boardSize.x)
				{
					for (int k = 0; k < boardSize.x; ++k)
					{
						grid[k][j].setTexture(emptyTex);
					}
					dropRow(j);
					clearedRows++;
				}
			}
		}
		counter = 0;
	}

	if (clearedRows > 0)
	{
		score += pointsPerRow[clearedRows - 1] * (level + 1);
	}

	return clearedRows;
}

void Board::dropRow(int y)
{
	for (int j = y; j > 0; --j)
	{
		for (int i = 0; i < boardSize.x; ++i)
		{
			grid[i][j].setTexture(*grid[i][j - 1].getTexture());
			grid[i][j].setColor(grid[i][j - 1].getColor());
		}
	}
}