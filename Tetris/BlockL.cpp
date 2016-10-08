#include "BlockL.h"


BlockL::BlockL(Board* b) : Block(b)
{
	board = b;
}


BlockL::~BlockL()
{
	
}

bool BlockL::spawn()
{
	// Orange color
	color = sf::Color(255, 130, 0);

	if (board->grid[board->getSpawnPoint().x][board->getSpawnPoint().y].getTexture() == &board->emptyTex &&
		board->grid[board->getSpawnPoint().x][board->getSpawnPoint().y + 1].getTexture() == &board->emptyTex &&
		board->grid[board->getSpawnPoint().x + 1][board->getSpawnPoint().y].getTexture() == &board->emptyTex &&
		board->grid[board->getSpawnPoint().x + 2][board->getSpawnPoint().y].getTexture() == &board->emptyTex)
	{
		positions[1] = sf::Vector2i(board->getSpawnPoint().x, board->getSpawnPoint().y);
		board->grid[positions[1].x][positions[1].y].setTexture(board->blockTex);
		board->grid[positions[1].x][positions[1].y].setColor(color);

		positions[0] = sf::Vector2i(board->getSpawnPoint().x, board->getSpawnPoint().y + 1);
		board->grid[positions[0].x][positions[0].y].setTexture(board->blockTex);
		board->grid[positions[0].x][positions[0].y].setColor(color);

		positions[2] = sf::Vector2i(board->getSpawnPoint().x + 1, board->getSpawnPoint().y);
		board->grid[positions[2].x][positions[2].y].setTexture(board->blockTex);
		board->grid[positions[2].x][positions[2].y].setColor(color);

		positions[3] = sf::Vector2i(board->getSpawnPoint().x + 2, board->getSpawnPoint().y);
		board->grid[positions[3].x][positions[3].y].setTexture(board->blockTex);
		board->grid[positions[3].x][positions[3].y].setColor(color);
	}

	else
	{
		return false;
	}

	return true;
}

void BlockL::rotate(int direction)
{

}
