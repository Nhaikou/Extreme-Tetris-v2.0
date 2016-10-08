#include "BlockS.h"


BlockS::BlockS(Board* b) : Block(b)
{
	board = b;
}


BlockS::~BlockS()
{

}

bool BlockS::spawn()
{
	color = sf::Color::Green;

	if (board->grid[board->getSpawnPoint().x][board->getSpawnPoint().y + 1].getTexture() == &board->emptyTex &&
		board->grid[board->getSpawnPoint().x + 1][board->getSpawnPoint().y + 1].getTexture() == &board->emptyTex &&
		board->grid[board->getSpawnPoint().x + 1][board->getSpawnPoint().y].getTexture() == &board->emptyTex &&
		board->grid[board->getSpawnPoint().x + 2][board->getSpawnPoint().y].getTexture() == &board->emptyTex)
	{
		positions[0] = sf::Vector2i(board->getSpawnPoint().x, board->getSpawnPoint().y + 1);
		board->grid[positions[0].x][positions[0].y].setTexture(board->blockTex);
		board->grid[positions[0].x][positions[0].y].setColor(color);

		positions[1] = sf::Vector2i(board->getSpawnPoint().x + 1, board->getSpawnPoint().y + 1);
		board->grid[positions[1].x][positions[1].y].setTexture(board->blockTex);
		board->grid[positions[1].x][positions[1].y].setColor(color);

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

void BlockS::rotate(int direction)
{
	for (int i = 0; i < tetra; ++i)
	{
		board->grid[positions[i].x][positions[i].y].setTexture(board->emptyTex);
	}

	// Rotate
	if (rotation == 0 && positions[0].y > 0 &&
		board->grid[positions[0].x + 1][positions[0].y - 1].getTexture() == &board->emptyTex &&
		board->grid[positions[1].x + 1][positions[1].y].getTexture() == &board->emptyTex &&
		board->grid[positions[2].x][positions[2].y - 1].getTexture() == &board->emptyTex)
	{
		positions[0] += sf::Vector2i(1, -1);
		positions[1] += sf::Vector2i(1, 0);
		positions[2] += sf::Vector2i(0, -1);

		rotation = 1;
	}
	else if (rotation == 1 && positions[0].x > 0 &&
		board->grid[positions[0].x - 1][positions[0].y + 1].getTexture() == &board->emptyTex &&
		board->grid[positions[1].x - 1][positions[1].y].getTexture() == &board->emptyTex &&
		board->grid[positions[2].x ][positions[2].y + 1].getTexture() == &board->emptyTex)
	{
		positions[0] += sf::Vector2i(-1, 1);
		positions[1] += sf::Vector2i(-1, 0);
		positions[2] += sf::Vector2i(0, 1);

		rotation = 0;
	}

	for (int i = 0; i < tetra; ++i)
	{
		board->grid[positions[i].x][positions[i].y].setTexture(board->blockTex);
		board->grid[positions[i].x][positions[i].y].setColor(color);
	}
}
