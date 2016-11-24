#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"
#include <vector>

class Player
{
public:
	Player(sf::Vector2u size, sf::Vector2i position, sf::Vector2u spawn, bool lastPlayer);
	~Player();
	
	void updateNextBlock(unsigned blockType);

	Board* board = nullptr;

	sf::Texture emptyTex;
	std::vector<std::vector<sf::Sprite>> nextBlockSprites;
	sf::Vector2u nextBlockSize = { 4, 2 }; // The amount of space we need to show our next block
};
#endif;

