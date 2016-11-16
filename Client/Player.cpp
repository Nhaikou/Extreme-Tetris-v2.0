#include "Player.h"


Player::Player(sf::Vector2u position, sf::Vector2i size, sf::Vector2u spawn)
{
	board = new Board(position, size, spawn);
}


Player::~Player()
{
}
