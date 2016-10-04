#include "BlockZ.h"


BlockZ::BlockZ(Board* b) : Block(b)
{
	board = b;
}


BlockZ::~BlockZ()
{

}

bool BlockZ::spawn()
{
	color = sf::Color::Red;

	unsigned counter = 0;

	if (board->board[board->getSpawnPoint().x][board->getSpawnPoint().y].getTexture() == &board->emptyTex)
	{
		positions[counter] = sf::Vector2i(board->getSpawnPoint().x, board->getSpawnPoint().y);
		board->board[positions[counter].x][positions[counter].y].setTexture(board->blockTex);
		board->board[positions[counter].x][positions[counter].y].setColor(color);

		positions[counter + 1] = sf::Vector2i(board->getSpawnPoint().x + 1, board->getSpawnPoint().y);
		board->board[positions[counter + 1].x][positions[counter].y].setTexture(board->blockTex);
		board->board[positions[counter + 1].x][positions[counter].y].setColor(color);

		positions[counter + 2] = sf::Vector2i(board->getSpawnPoint().x + 1, board->getSpawnPoint().y + 1);
		board->board[positions[counter + 2].x][positions[counter].y].setTexture(board->blockTex);
		board->board[positions[counter + 2].x][positions[counter].y].setColor(color);

		positions[counter + 3] = sf::Vector2i(board->getSpawnPoint().x + 2, board->getSpawnPoint().y + 1);
		board->board[positions[counter + 3].x][positions[counter].y].setTexture(board->blockTex);
		board->board[positions[counter + 3].x][positions[counter].y].setColor(color);
	}
	
	else
	{
		return false;
	}

	return true;
}
