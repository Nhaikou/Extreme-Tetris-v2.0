#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>

#include <vector>
#include <iostream>

class Board
{
public:
	Board(sf::Vector2u size, sf::Vector2i boardPos, sf::Vector2u spawn);
	~Board();

	sf::Vector2u getSize();
	sf::Vector2i getBoardPosition();
	sf::Vector2u getSpawnPoint();

	unsigned clearRow();
	void dropRow(int y);

	std::vector<std::vector<sf::Sprite>> grid, updatedGrid;
	sf::Texture blockTex, emptyTex;

	sf::Vector2f dropTime = { 0, 0 }; // Drop time for blocks
	unsigned int counter = 0; // Counter for how many rows are cleared
	const int maxRows = 20;	// Max number of cleared rows before speed increases
	const int dropTimeReduction = 100;	// Drop time reduction for speed

private:
	sf::Sprite block;
	sf::Vector2u boardSize, spawnPoint;
	sf::Vector2i boardPosition;
};

#endif