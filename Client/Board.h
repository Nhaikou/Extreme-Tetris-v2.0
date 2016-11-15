#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <SFML/Graphics.hpp>

class Board
{
public:
	Board();
	~Board();

	std::vector<std::vector<sf::Sprite>> grid;
};

#endif