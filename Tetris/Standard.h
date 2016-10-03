#ifndef STANDARD_H
#define STANDARD_H

#include "State.h"
#include "Board.h"
#include "Block.h"
#include "BlockI.h"

class Standard : public State
{
public:
	Standard(StateMachine* sm);
	~Standard();

	void handleInput();
	void update(const float dt);
	void draw(const float dt);

	void spawnBlock();

protected:
	void onInitialize();

private:
	sf::Vector2f dropTime = { 0, 0 };

	Board *board = nullptr;
	Block *currentBlock = nullptr;
};

#endif