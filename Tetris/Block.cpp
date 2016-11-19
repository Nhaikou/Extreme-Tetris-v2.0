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
		if (board->grid[positions[i].x - 1][positions[i].y].z != BlockType::EMPTY)
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
		board->grid[positions[i].x][positions[i].y].z = BlockType::EMPTY;
		positions[i].x--;
		board->grid[positions[i].x][positions[i].y].z = type;
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
		if (board->grid[positions[i].x + 1][positions[i].y].z != BlockType::EMPTY)
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
		board->grid[positions[i].x][positions[i].y].z = BlockType::EMPTY;
		positions[i].x++;
		board->grid[positions[i].x][positions[i].y].z = type;
	}
}

void Block::dropDown()
{
	while (moveDown());
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
		if (board->grid[positions[i].x][positions[i].y + 1].z != BlockType::EMPTY)
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
		board->grid[positions[i].x][positions[i].y].z = BlockType::EMPTY;
		positions[i].y++;
		board->grid[positions[i].x][positions[i].y].z = type;
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

unsigned Block::getType()
{
	return type;
}