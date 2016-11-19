#include "BlockJ.h"


BlockJ::BlockJ(Board* b) : Block(b)
{
	board = b;
}


BlockJ::~BlockJ()
{

}

bool BlockJ::spawn()
{
	type = BlockType::BLOCKJ;

	if (board->grid[board->getSpawnPoint().x][board->getSpawnPoint().y] == BlockType::EMPTY &&
		board->grid[board->getSpawnPoint().x + 1][board->getSpawnPoint().y] == BlockType::EMPTY &&
		board->grid[board->getSpawnPoint().x + 2][board->getSpawnPoint().y] == BlockType::EMPTY &&
		board->grid[board->getSpawnPoint().x + 2][board->getSpawnPoint().y + 1] == BlockType::EMPTY)
	{
		positions[0] = sf::Vector2i(board->getSpawnPoint().x, board->getSpawnPoint().y);
		board->grid[positions[0].x][positions[0].y] = BlockType::BLOCKJ;

		positions[2] = sf::Vector2i(board->getSpawnPoint().x + 1, board->getSpawnPoint().y);
		board->grid[positions[2].x][positions[2].y] = BlockType::BLOCKJ;

		positions[3] = sf::Vector2i(board->getSpawnPoint().x + 2, board->getSpawnPoint().y);
		board->grid[positions[3].x][positions[3].y] = BlockType::BLOCKJ;

		positions[1] = sf::Vector2i(board->getSpawnPoint().x + 2, board->getSpawnPoint().y + 1);
		board->grid[positions[1].x][positions[1].y] = BlockType::BLOCKJ;
	}

	else
	{
		return false;
	}

	return true;
}

void BlockJ::rotate(int direction)
{
	for (int i = 0; i < tetra; ++i)
	{
		board->grid[positions[i].x][positions[i].y] = BlockType::EMPTY;
	}

	// Clockwise rotation
	if (direction == 1)
	{
		if (rotation == 0 && board->grid[positions[0].x][positions[0].y + 1]== BlockType::EMPTY &&
			board->grid[positions[1].x - 1][positions[1].y] == BlockType::EMPTY &&
			board->grid[positions[2].x][positions[2].y] == BlockType::EMPTY &&
			board->grid[positions[3].x - 1][positions[3].y - 1] == BlockType::EMPTY)
		{
			positions[0] += sf::Vector2i(0, 1);
			positions[1] += sf::Vector2i(-1, 0);
			positions[2] += sf::Vector2i(0, 0);
			positions[3] += sf::Vector2i(-1, -1);

			rotation = 1;
		}
		else if (rotation == 1 && positions[2].x + 1 < board->getSize().x && board->grid[positions[0].x][positions[0].y - 1] == BlockType::EMPTY &&
			board->grid[positions[1].x][positions[1].y - 1] == BlockType::EMPTY &&
			board->grid[positions[2].x + 1][positions[2].y] == BlockType::EMPTY &&
			board->grid[positions[3].x - 1][positions[3].y] == BlockType::EMPTY)
		{
			positions[0] += sf::Vector2i(0, -1);
			positions[1] += sf::Vector2i(0, -1);
			positions[2] += sf::Vector2i(1, 0);
			positions[3] += sf::Vector2i(-1, 0);

			rotation = 2;
		}
		else if (rotation == 2 && positions[1].y + 1 < board->getSize().y && board->grid[positions[0].x + 1][positions[0].y + 1] == BlockType::EMPTY &&
			board->grid[positions[1].x][positions[1].y] == BlockType::EMPTY &&
			board->grid[positions[2].x - 1][positions[2].y - 1] == BlockType::EMPTY &&
			board->grid[positions[3].x + 2][positions[3].y] == BlockType::EMPTY)
		{
			positions[0] += sf::Vector2i(1, 1);
			positions[1] += sf::Vector2i(0, 0);
			positions[2] += sf::Vector2i(-1, -1);
			positions[3] += sf::Vector2i(2, 0);

			rotation = 3;
		}
		else if (rotation == 3 && positions[1].x > 0 && board->grid[positions[0].x - 1][positions[0].y - 1] == BlockType::EMPTY &&
			board->grid[positions[1].x + 1][positions[1].y + 1] == BlockType::EMPTY &&
			board->grid[positions[2].x][positions[2].y + 1] == BlockType::EMPTY &&
			board->grid[positions[3].x][positions[3].y + 1] == BlockType::EMPTY)
		{
			positions[0] += sf::Vector2i(-1, -1);
			positions[1] += sf::Vector2i(1, 1);
			positions[2] += sf::Vector2i(0, 1);
			positions[3] += sf::Vector2i(0, 1);

			rotation = 0;
		}
	}

	// Counter clockwise rotation
	else if (direction == -1)
	{
		if (rotation == 0 && board->grid[positions[0].x + 1][positions[0].y + 1] == BlockType::EMPTY &&
			board->grid[positions[1].x - 1][positions[1].y - 1] == BlockType::EMPTY &&
			board->grid[positions[2].x][positions[2].y - 1] == BlockType::EMPTY &&
			board->grid[positions[3].x][positions[3].y - 1] == BlockType::EMPTY)
		{
			positions[0] += sf::Vector2i(1, 1);
			positions[1] += sf::Vector2i(-1, -1);
			positions[2] += sf::Vector2i(0, -1);
			positions[3] += sf::Vector2i(0, -1);

			rotation = 3;
		}
		else if (rotation == 1 && positions[2].x + 1 < board->getSize().x && board->grid[positions[0].x + 1][positions[0].y] == BlockType::EMPTY &&
			board->grid[positions[1].x + 1][positions[1].y] == BlockType::EMPTY &&
			board->grid[positions[2].x][positions[2].y] == BlockType::EMPTY &&
			board->grid[positions[3].x + 1][positions[3].y + 1] == BlockType::EMPTY)
		{
			positions[0] += sf::Vector2i(0, -1);
			positions[1] += sf::Vector2i(1, 0);
			positions[2] += sf::Vector2i(0, 0);
			positions[3] += sf::Vector2i(1, 1);

			rotation = 0;
		}
		else if (rotation == 2 && positions[1].y + 1 < board->getSize().y && board->grid[positions[0].x][positions[0].y + 1] == BlockType::EMPTY &&
			board->grid[positions[1].x][positions[1].y + 1] == BlockType::EMPTY &&
			board->grid[positions[2].x - 1][positions[2].y] == BlockType::EMPTY &&
			board->grid[positions[3].x + 1][positions[3].y] == BlockType::EMPTY)
		{
			positions[0] += sf::Vector2i(0, 1);
			positions[1] += sf::Vector2i(0, 1);
			positions[2] += sf::Vector2i(-1, 0);
			positions[3] += sf::Vector2i(1, 0);

			rotation = 1;
		}
		else if (rotation == 3 && positions[1].x > 0 && board->grid[positions[0].x - 1][positions[0].y - 1] == BlockType::EMPTY &&
			board->grid[positions[1].x][positions[1].y] == BlockType::EMPTY &&
			board->grid[positions[2].x + 1][positions[2].y + 1] == BlockType::EMPTY &&
			board->grid[positions[3].x - 2][positions[3].y] == BlockType::EMPTY)
		{
			positions[0] += sf::Vector2i(-1, -1);
			positions[1] += sf::Vector2i(0, 0);
			positions[2] += sf::Vector2i(1, 1);
			positions[3] += sf::Vector2i(-2, 0);

			rotation = 2;
		}
	}

	for (int i = 0; i < tetra; ++i)
	{
		board->grid[positions[i].x][positions[i].y] = BlockType::BLOCKJ;
	}
}