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
	for (int i = 0; i < tetra; i++)
	{
		if (positions[i].x - 1 < 0)
		{
			return;
		}
		if (board->board[positions[i].x - 1][positions[i].y].getTexture() != &board->emptyTex)
		{
			bool ok = false;
			for (int j = 0; j < tetra; j++)
			{
				if (positions[j].x == positions[i].x - 1 && positions[j].y == positions[i].y)
				{
					ok = true;
				}
			}
			if (ok == false)
			{
				return;
			}
		}
	}

	for (int i = 0; i < tetra; i++)
	{
		board->board[positions[i].x][positions[i].y].setTexture(board->emptyTex);
		positions[i].x--;
		board->board[positions[i].x][positions[i].y].setTexture(board->blockTex);
		board->board[positions[i].x][positions[i].y].setColor(color);
	}
}

void Block::moveRight()
{
	for (int i = 0; i < tetra; i++)
	{
		if (positions[i].x + 1 >= board->getBoardSize().x)
		{
			return;
		}
		if (board->board[positions[i].x + 1][positions[i].y].getTexture() != &board->emptyTex)
		{
			bool ok = false;
			for (int j = 0; j < tetra; j++)
			{
				if (positions[j].x == positions[i].x + 1 && positions[j].y == positions[i].y)
				{
					ok = true;
				}
			}
			if (ok == false)
			{
				return;
			}
		}
	}

	for (int i = tetra - 1; i >= 0; i--)
	{
		board->board[positions[i].x][positions[i].y].setTexture(board->emptyTex);
		positions[i].x++;
		board->board[positions[i].x][positions[i].y].setTexture(board->blockTex);
		board->board[positions[i].x][positions[i].y].setColor(color);
	}
}

bool Block::moveDown()
{
	for (int i = 0; i < tetra; i++)
	{
		if (positions[i].y + 1 >= board->getBoardSize().y)
		{
			return false;
		}
		if (board->board[positions[i].x][positions[i].y + 1].getTexture() != &board->emptyTex)
		{
			bool ok = false;
			for (int j = 0; j < tetra; j++)
			{
				if (positions[j].y == positions[i].y + 1 && positions[j].x == positions[i].x)
				{
					ok = true;
				}
			}
			if (ok == false)
			{
				return false;
			}
		}
	}

	for (int i = 0; i < tetra; i++)
	{
		board->board[positions[i].x][positions[i].y].setTexture(board->emptyTex);
		positions[i].y++;
		board->board[positions[i].x][positions[i].y].setTexture(board->blockTex);
		board->board[positions[i].x][positions[i].y].setColor(color);
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