#ifndef FACTORY_H
#define FACTORY_H

#include "State.h"
#include "Board.h"
#include "Block.h"
#include "BlockI.h"
#include "BlockO.h"
#include "BlockZ.h"
#include "BlockS.h"
#include "BlockL.h"
#include "BlockJ.h"
#include "BlockT.h"

class Factory : public State
{
public:
	Factory(StateMachine* sm);
	~Factory();

	void handleInput();
	void update(const float dt);
	void draw(const float dt);

	void spawnBlock();
	void moveLineLeft();
	void moveLineRight();

protected:
	void onInitialize();

private:
	int lineDirection = 1;
	sf::Vector2f dropTime = { 0, 0 }, lineTime = { 0, 0 };
	Board *board = nullptr;
	Block *currentBlock = nullptr;
};

#endif