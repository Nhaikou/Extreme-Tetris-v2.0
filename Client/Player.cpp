#include "Player.h"


Player::Player(sf::Vector2u size, sf::Vector2i position, sf::Vector2u spawn, bool lastPlayer)
{
	board = new Board(size, position, spawn, lastPlayer);
}

Player::~Player()
{
}
