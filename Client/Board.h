#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <SFML/Graphics.hpp>

enum BlockType
{
	EMPTY = 0,
	BLOCKI = 1,
	BLOCKO = 2,
	BLOCKZ = 3,
	BLOCKS = 4,
	BLOCKL = 5,
	BLOCKJ = 6,
	BLOCKT = 7,
};

class Board
{
public:
	Board(sf::Vector2u boardSize, sf::Vector2i boardPos, sf::Vector2u spawn);
	~Board();

	std::vector<std::vector<sf::Sprite>> grid;

	sf::Vector2u getSize();
	sf::Vector2i getPosition();
	sf::Vector2u getSpawnPoint();

private:
	sf::Vector2u size, spawnPoint, blockSize = { 16, 16 };
	sf::Vector2i position;
	sf::Texture blockTex, emptyTex;
	sf::Sprite block;
};

#endif