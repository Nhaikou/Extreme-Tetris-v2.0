#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"
#include <vector>

class Player
{
public:
	Player(sf::Vector2u position, sf::Vector2i size, sf::Vector2u spawn);
	~Player();

	Board* board = nullptr;
};
#endif;

