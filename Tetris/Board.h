#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>

#include <vector>
#include <iostream>

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

	sf::Vector2u getSize();
	sf::Vector2i getPosition();
	sf::Vector2u getSpawnPoint();
	unsigned getScore();
	unsigned getLevel();

	unsigned clearRow();
	void dropRow(int y);
	void setScore(unsigned scr);
	void setLevel(unsigned lvl);

	std::vector<std::vector<unsigned>> grid, updatedGrid;
	std::vector<unsigned> gridSlice, updatedGridSlice;

	sf::Vector2f dropTime = { 0, 0 }; // Drop time for blocks
	unsigned int counter = 0; // Counter for how many rows are cleared
	const int maxRows = 20;	// Max number of cleared rows before speed increases
	const int dropTimeReduction = 100;	// Drop time reduction for speed

private:
	sf::Vector2u size, spawnPoint, blockSize = { 16, 16 };
	sf::Vector2i position;
	unsigned level = 0, score = 0;
	std::vector<unsigned> pointsPerRow;
};

#endif