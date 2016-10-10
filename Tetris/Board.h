#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>

#include <vector>

class Board
{
public:
	Board(sf::Vector2u size, sf::Vector2i boardPos, sf::Vector2u spawn);
	~Board();

	sf::Vector2u getSize();
	sf::Vector2i getBoardPosition();
	sf::Vector2u getSpawnPoint();

	std::vector<std::vector<sf::Sprite>> grid, updatedGrid;
	sf::Texture blockTex, emptyTex;

private:
	sf::Sprite block;
	sf::Vector2u boardSize, spawnPoint;
	sf::Vector2i boardPosition;
};

#endif