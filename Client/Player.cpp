#include "Player.h"


Player::Player(sf::Vector2u size, sf::Vector2i position, sf::Vector2u spawn)
{
	board = new Board(size, position, spawn);
}


Player::~Player()
{
}
