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
	color = sf::Color::Yellow;

	unsigned counter = 0;
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 1; j >= 0; --j)
		{
			if (board->board[board->getSpawnPoint().x + i][board->getSpawnPoint().y + j].getTexture() == &board->emptyTex)
			{ 
				positions[counter] = sf::Vector2i(board->getSpawnPoint().x + i, board->getSpawnPoint().y + j);
				board->board[positions[counter].x][positions[counter].y].setTexture(board->blockTex);
				board->board[positions[counter].x][positions[counter].y].setColor(color);
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