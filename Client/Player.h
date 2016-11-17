#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"
#include <vector>

class Player
{
public:
	Player(sf::Vector2u size, sf::Vector2i position, sf::Vector2u spawn);
	~Player();

	Board* board = nullptr;
};
#endif;

