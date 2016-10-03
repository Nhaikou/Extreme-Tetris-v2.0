#include "Board.h"

Board::Board(sf::Vector2u size, sf::Vector2i boardPos, sf::Vector2u spawn)
{
	blockTex.loadFromFile("../Assets/Block.png");
	block.setTexture(blockTex);
	emptyTex.create(blockTex.getSize().x, blockTex.getSize().y);
	block.setTexture(emptyTex);

	boardSize = size;
	boardPosition = boardPos;
	spawnPoint = spawn;

	board.resize(boardSize.x);
	for (int i = 0; i < boardSize.x; ++i)
	{
		board[i].resize(boardSize.y);
	}

	for (int j = 0; j < boardSize.y; j++)
	{
		for (int i = 0; i < boardSize.x; i++)
		{
			board[i][j] = block;
			board[i][j].setPosition(boardPosition.x + block.getGlobalBounds().width * i, boardPosition.y + block.getGlobalBounds().height * j);
		}
	}

	updatedBoard = board;
}

Board::~Board()
{

}

sf::Vector2u Board::getBoardSize()
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