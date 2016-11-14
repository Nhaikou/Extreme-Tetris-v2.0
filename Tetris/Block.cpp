#include "Block.h"

Block::Block(Board *b)
{
	board = b;
	positions.resize(tetra);
}

Block::~Block()
{

}

void Block::moveLeft()
{
	// Go through all the smaller blocks in our current block type
	for (int i = 0; i < tetra; ++i)
	{
		// Make sure that we can't move out of the grid
		if (positions[i].x - 1 < 0)
		{
			return;
		}
		// Check if there's an empty space next to (left) the current block
		if (board->grid[positions[i].x - 1][positions[i].y].getTexture() != &board->emptyTex)
		{
			// Check if the space that had a texture is part of the current block type
			bool ok = false;
			for (int j = 0; j < tetra; ++j)
			{
				if (positions[j].x == positions[i].x - 1 && positions[j].y == positions[i].y)
				{
					ok = true;
				}
			}
			// If the textured space is not one of the blocks you're moving, you can't move left
			if (ok == false)
			{
				return;
			}
		}
	}

	// There are no obstacles so we can move our block
	for (int i = 0; i < tetra; ++i)
	{
		// Clear the current blocks, change the x-positions by -1 and set the texture and color
		board->grid[positions[i].x][positions[i].y].setTexture(board->emptyTex);
		positions[i].x--;
		board->grid[positions[i].x][positions[i].y].setTexture(board->blockTex);
		board->grid[positions[i].x][positions[i].y].setColor(color);
	}
}

void Block::moveRight()
{
	// Go through all the smaller blocks in our current block type
	for (int i = 0; i < tetra; ++i)
	{
		// Make sure that we can't move out of the grid
		if (positions[i].x + 1 >= board->getSize().x)
		{
			return;
		}
		// Check if there's an empty space next to (right) the current block
		if (board->grid[positions[i].x + 1][positions[i].y].getTexture() != &board->emptyTex)
		{
			// Check if the space that had a texture is part of the current block type
			bool ok = false;
			for (int j = 0; j < tetra; ++j)
			{
				if (positions[j].x == positions[i].x + 1 && positions[j].y == positions[i].y)
				{
					ok = true;
				}
			}
			// If the textured space is not one of the blocks you're moving, you can't move right
			if (ok == false)
			{
				return;
			}
		}
	}

	// There are no obstacles so we can move our block
	for (int i = tetra - 1; i >= 0; --i)
	{
		// Clear the current blocks, change the x-positions by +1 and set the texture and color
		board->grid[positions[i].x][positions[i].y].setTexture(board->emptyTex);
		positions[i].x++;
		board->grid[positions[i].x][positions[i].y].setTexture(board->blockTex);
		board->grid[positions[i].x][positions[i].y].setColor(color);
	}
}

bool Block::moveDown()
{
	// Go through all the smaller blocks in our current block type
	for (int i = 0; i < tetra; ++i)
	{
		// Make sure that we can't move out of the grid
		if (positions[i].y + 1 >= board->getSize().y)
		{
			return false;
		}
		// Check if there's an empty space next to (down) the current block
		if (board->grid[positions[i].x][positions[i].y + 1].getTexture() != &board->emptyTex)
		{
			// Check if the space that had a texture is part of the current block type
			bool ok = false;
			for (int j = 0; j < tetra; ++j)
			{
				if (positions[j].y == positions[i].y + 1 && positions[j].x == positions[i].x)
				{
					ok = true;
				}
			}
			// If the textured space is not one of the blocks you're moving, you can't move down
			if (ok == false)
			{
				return false;
			}
		}
	}

	// There are no obstacles so we can move our block
	for (int i = 0; i < tetra; ++i)
	{
		// Clear the current blocks, change the x-positions by +1 and set the texture and color
		board->grid[positions[i].x][positions[i].y].setTexture(board->emptyTex);
		positions[i].y++;
		board->grid[positions[i].x][positions[i].y].setTexture(board->blockTex);
		board->grid[positions[i].x][positions[i].y].setColor(color);
	}

	return true;
}

bool Block::spawn()
{
	return false;
}

void Block::rotate(int direction)
{
	direction;
}

sf::Color Block::getColor()
{
	return color;
}

MinMaxPositions Block::calculateMinAndMaxPositions()
{
	minMaxPositions.minX = positions[0].x, minMaxPositions.maxX = positions[0].x, minMaxPositions.minY = positions[0].y, minMaxPositions.maxY = positions[0].y;
	for (int i = 1; i < positions.size(); ++i)
	{
		if (positions[i].x < minMaxPositions.minX)
		{
			minMaxPositions.minX = positions[i].x;
		}
		if (positions[i].x > minMaxPositions.maxX)
		{
			minMaxPositions.maxX = positions[i].x;
		}
		if (positions[i].y < minMaxPositions.minY)
		{
			minMaxPositions.minY = positions[i].y;
		}
		if (positions[i].y > minMaxPositions.maxY)
		{
			minMaxPositions.maxY = positions[i].y;
		}
	}

	minMaxPositions.minX = board->getBoardPosition().x + (minMaxPositions.minX * board->blockTex.getSize().x) - board->blockTex.getSize().x;
	minMaxPositions.maxX = board->getBoardPosition().x + ((minMaxPositions.maxX + 1) * board->blockTex.getSize().x) - minMaxPositions.minX + board->blockTex.getSize().x;
	minMaxPositions.minY = board->getBoardPosition().y + (minMaxPositions.minY * board->blockTex.getSize().y) - board->blockTex.getSize().y;
	minMaxPositions.maxY = board->getBoardPosition().y + ((minMaxPositions.maxY + 1) * board->blockTex.getSize().y) - minMaxPositions.minY + board->blockTex.getSize().y;

	return minMaxPositions;
}