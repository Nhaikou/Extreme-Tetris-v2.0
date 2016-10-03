#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>

#include <vector>

class Board
{
public:
	Board(sf::Vector2u size, sf::Vector2u boardPos);
	~Board();

	sf::Vector2u getBoardSize();
	sf::Vector2u getBoardPosition();

	std::vector<std::vector<sf::Sprite>> board;

private:
	sf::Sprite block;
	sf::Texture blockTex, emptyTex;
	sf::Vector2u boardSize, boardPosition;
};

#endif