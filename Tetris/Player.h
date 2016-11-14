#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"
#include "Bag.h"
#include "Block.h"
#include "BlockI.h"
#include "BlockO.h"
#include "BlockZ.h"
#include "BlockS.h"
#include "BlockL.h"
#include "BlockJ.h"
#include "BlockT.h"
#include <vector>

class Player
{
public:
	Player();
	~Player();

	bool updateClient();
	bool spawnBlock();

	void dropUpdate(const float dt);

	int clientKey = -1;	// Clients keys for gameplay. Must be -1 (unknown), that the server doesn't register any keys pressed from the start.

	Board* board = nullptr;
	Block* currentBlock = nullptr;
	Bag bag;
};
#endif;

