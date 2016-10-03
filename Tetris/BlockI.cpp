#include "BlockI.h"

BlockI::BlockI(Board *b) : Block(b)
{
	
}

BlockI::~BlockI()
{

}

bool BlockI::spawn()
{
	color = sf::Color::Cyan;
	for (int i = 0; i < tetra; i++)
	{
		if (board->board[board->getSpawnPoint().x + i][board->getSpawnPoint().y].getTexture() == &board->emptyTex)
		{
			positions[i] = sf::Vector2i(board->getSpawnPoint().x + i, board->getSpawnPoint().y);
			board->board[positions[i].x][positions[i].y].setTexture(board->blockTex);
			board->board[positions[i].x][positions[i].y].setColor(color);
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
	for (int i = 0; i < tetra; i++)
	{
		board->board[positions[i].x][positions[i].y].setTexture(board->emptyTex);
	}

	if (rotation == 1 && positions[1].x > 0 && positions[1].x + 2 < board->getBoardSize().x &&
		board->board[positions[0].x - 1][positions[0].y - 1].getTexture() == &board->emptyTex &&
		board->board[positions[2].x + 1][positions[2].y + 1].getTexture() == &board->emptyTex &&
		board->board[positions[3].x + 2][positions[3].y + 2].getTexture() == &board->emptyTex)
	{
		positions[0] += sf::Vector2i(-1, -1);
		positions[2] += sf::Vector2i(1, 1);
		positions[3] += sf::Vector2i(2, 2);

		rotation = 0;
	}
	else if (rotation == 0 && positions[1].y - 1 > 0 && positions[1].y + 1 < board->getBoardSize().y &&
		board->board[positions[0].x + 1][positions[0].y + 1].getTexture() == &board->emptyTex &&
		board->board[positions[2].x - 1][positions[2].y - 1].getTexture() == &board->emptyTex &&
		board->board[positions[3].x - 2][positions[3].y - 2].getTexture() == &board->emptyTex)
	{
		positions[0] += sf::Vector2i(1, 1);
		positions[2] += sf::Vector2i(-1, -1);
		positions[3] += sf::Vector2i(-2, -2);

		rotation = 1;
	}

	for (int i = 0; i < tetra; i++)
	{
		board->board[positions[i].x][positions[i].y].setTexture(board->blockTex);
		board->board[positions[i].x][positions[i].y].setColor(color);
	}
}